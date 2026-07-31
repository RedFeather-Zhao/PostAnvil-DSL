package org.postanvil;

/** Minimal JNI bridge. Keep one NativeBridge.Program per compiled DSL source. */
public final class NativeBridge {
    static {
        System.loadLibrary("postanvil_jni");
    }

    private NativeBridge() {}

    public static native String version();
    private static native long compile(String source);
    private static native void destroyProgram(long handle);
    private static native long[] evaluateCounts(
        long handle,
        double imageWidth,
        double imageHeight,
        String[] classes,
        double[] boxes);

    public static final class Program implements AutoCloseable {
        private long handle;

        public Program(String source) {
            handle = compile(source);
        }

        public synchronized long[] evaluateCounts(
            double imageWidth,
            double imageHeight,
            String[] classes,
            double[] boxes) {
            if (handle == 0) throw new IllegalStateException("Program is closed");
            return NativeBridge.evaluateCounts(
                handle, imageWidth, imageHeight, classes, boxes);
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
