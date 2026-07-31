param(
	[ValidateSet('Debug', 'Release')]
	[string]$Configuration = 'Release',
	[switch]$StaticOnly
)

$ErrorActionPreference = 'Stop'
$projectRoot = Split-Path -Parent $PSScriptRoot
$configurationLower = $Configuration.ToLowerInvariant()
$buildDir = Join-Path $projectRoot "out/build/package-$configurationLower"
$installDir = Join-Path $projectRoot "out/install/$configurationLower"

$shared = if ($StaticOnly) { 'OFF' } else { 'ON' }

cmake -S $projectRoot -B $buildDir -G Ninja `
	"-DCMAKE_BUILD_TYPE=$Configuration" `
	-DPOSTANVIL_BUILD_STATIC=ON `
	"-DPOSTANVIL_BUILD_SHARED=$shared" `
	-DPOSTANVIL_BUILD_TESTS=OFF `
	"-DCMAKE_INSTALL_PREFIX=$installDir"
cmake --build $buildDir --parallel
cmake --install $buildDir
cmake --build $buildDir --target package
