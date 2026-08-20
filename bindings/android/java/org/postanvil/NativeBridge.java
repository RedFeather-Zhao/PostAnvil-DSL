package org.postanvil;

import java.util.Arrays;
import java.util.Objects;

/** JNI bridge for compiling and evaluating PostAnvil programs on Android. */
public final class NativeBridge {
    /** Reserved built-in category containing the Scene's input instance IDs. */
    public static final String ALL_INST = "ALL_INST";

    static {
        System.loadLibrary("postanvil_jni");
    }

    private NativeBridge() {}

    public static native String version();
    private static native long compile(String source);
    private static native void destroyProgram(long handle);
    private static native SceneResult evaluate(
        long handle,
        double imageWidth,
        double imageHeight,
        String[] classes,
        double[] boxes);

    /**
     * Immutable flattened view of the output Scene class memberships.
     *
     * <p>Each row contains one class name, one stable Scene instance ID, and
     * five box values in {@code [x, y, width, height, confidence]} order. The
     * same instance may appear in several rows when it belongs to several
     * classes; those rows retain the same instance ID. The built-in
     * {@link NativeBridge#ALL_INST} category is carried separately and is not
     * mixed into these ordinary-class rows.</p>
     */
    public static final class SceneResult {
        private static final int BOX_VALUE_COUNT = 5;

        private final String[] classes;
        private final long[] instanceIds;
        private final double[] boxes;
        private final long[] allInstanceIds;
        private final double[] allInstanceBoxes;

        private SceneResult(
            String[] classes,
            long[] instanceIds,
            double[] boxes,
            long[] allInstanceIds,
            double[] allInstanceBoxes) {
            if (classes.length != instanceIds.length
                || boxes.length != classes.length * BOX_VALUE_COUNT
                || allInstanceBoxes.length != allInstanceIds.length * BOX_VALUE_COUNT) {
                throw new IllegalArgumentException("Invalid native SceneResult array lengths");
            }
            this.classes = classes;
            this.instanceIds = instanceIds;
            this.boxes = boxes;
            this.allInstanceIds = allInstanceIds;
            this.allInstanceBoxes = allInstanceBoxes;
        }

        public int size() {
            return classes.length;
        }

        public String className(int index) {
            return classes[index];
        }

        public long instanceId(int index) {
            return instanceIds[index];
        }

        public double[] box(int index) {
            final int begin = index * BOX_VALUE_COUNT;
            return Arrays.copyOfRange(boxes, begin, begin + BOX_VALUE_COUNT);
        }

        public long count(String className) {
            Objects.requireNonNull(className, "className");
            if (ALL_INST.equalsIgnoreCase(className)) return allInstanceIds.length;
            long count = 0;
            for (String name : classes) {
                if (name.equalsIgnoreCase(className)) ++count;
            }
            return count;
        }

        public String[] classNames() {
            return classes.clone();
        }

        public long[] instanceIds() {
            return instanceIds.clone();
        }

        public double[] boxes() {
            return boxes.clone();
        }

        /** Number of members currently retained by the ALL_INST built-in category. */
        public int allInstanceCount() {
            return allInstanceIds.length;
        }

        public long allInstanceId(int index) {
            return allInstanceIds[index];
        }

        public double[] allInstanceBox(int index) {
            final int begin = index * BOX_VALUE_COUNT;
            return Arrays.copyOfRange(
                allInstanceBoxes, begin, begin + BOX_VALUE_COUNT);
        }

        public long[] allInstanceIds() {
            return allInstanceIds.clone();
        }

        public double[] allInstanceBoxes() {
            return allInstanceBoxes.clone();
        }
    }

    /** Keep one Program per compiled DSL source and reuse it across images. */
    public static final class Program implements AutoCloseable {
        private long handle;

        public Program(String source) {
            handle = compile(Objects.requireNonNull(source, "source"));
        }

        public synchronized SceneResult evaluate(
            double imageWidth,
            double imageHeight,
            String[] classes,
            double[] boxes) {
            if (handle == 0) throw new IllegalStateException("Program is closed");
            Objects.requireNonNull(classes, "classes");
            Objects.requireNonNull(boxes, "boxes");
            if (boxes.length != classes.length * SceneResult.BOX_VALUE_COUNT) {
                throw new IllegalArgumentException(
                    "boxes must contain [x,y,w,h,confidence] per class entry");
            }
            for (String className : classes) {
                Objects.requireNonNull(className, "classes must not contain null entries");
                if (ALL_INST.equalsIgnoreCase(className)) {
                    throw new IllegalArgumentException(
                        "classes must not contain the reserved built-in class ALL_INST");
                }
            }
            return NativeBridge.evaluate(handle, imageWidth, imageHeight, classes, boxes);
        }

        public synchronized long[] evaluateCounts(
            double imageWidth,
            double imageHeight,
            String[] classes,
            double[] boxes,
            String[] outputClasses) {
            Objects.requireNonNull(outputClasses, "outputClasses");
            final SceneResult result = evaluate(imageWidth, imageHeight, classes, boxes);
            final long[] counts = new long[outputClasses.length];
            for (int i = 0; i < outputClasses.length; ++i) {
                counts[i] = result.count(outputClasses[i]);
            }
            return counts;
        }

        public synchronized long[] evaluateCounts(
            double imageWidth,
            double imageHeight,
            String[] classes,
            double[] boxes) {
            return evaluateCounts(imageWidth, imageHeight, classes, boxes, classes);
        }

        @Override
        public synchronized void close() {
            if (handle != 0) {
                destroyProgram(handle);
                handle = 0;
            }
        }
    }
}
