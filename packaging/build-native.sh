#!/usr/bin/env sh
set -eu

configuration="${1:-Release}"
project_root=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)
configuration_lower=$(printf '%s' "$configuration" | tr '[:upper:]' '[:lower:]')
build_dir="$project_root/out/build/package-$configuration_lower"
install_dir="$project_root/out/install/$configuration_lower"

cmake -S "$project_root" -B "$build_dir" -G Ninja \
  -DCMAKE_BUILD_TYPE="$configuration" \
  -DPOSTANVIL_BUILD_STATIC=ON \
  -DPOSTANVIL_BUILD_SHARED=ON \
  -DPOSTANVIL_BUILD_TESTS=OFF \
  -DCMAKE_INSTALL_PREFIX="$install_dir"
cmake --build "$build_dir" --parallel
cmake --install "$build_dir"
cmake --build "$build_dir" --target package
