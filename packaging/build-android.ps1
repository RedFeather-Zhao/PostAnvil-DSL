param(
	[string]$NdkPath = $env:ANDROID_NDK_HOME,
	[ValidateSet('arm64-v8a', 'armeabi-v7a')]
	[string[]]$Abis = @('arm64-v8a', 'armeabi-v7a'),
	[ValidateRange(1, 64)]
	[int]$Parallel = 4
)

$ErrorActionPreference = 'Stop'

if ([string]::IsNullOrWhiteSpace($NdkPath)) {
	throw 'Specify -NdkPath or set ANDROID_NDK_HOME before building.'
}

$presetByAbi = @{
	'arm64-v8a' = 'android-arm64-release'
	'armeabi-v7a' = 'android-armv7-release'
}

foreach ($abi in $Abis) {
	$preset = $presetByAbi[$abi]
	Write-Host "Configuring PostAnvil for $abi"
	cmake --preset $preset "-DPOSTANVIL_ANDROID_NDK=$NdkPath"
	if ($LASTEXITCODE -ne 0) {
		throw "CMake configure failed for $abi."
	}

	Write-Host "Building and installing PostAnvil for $abi"
	cmake --build --preset "${preset}-install" --parallel $Parallel
	if ($LASTEXITCODE -ne 0) {
		throw "CMake build failed for $abi."
	}
}

Write-Host 'Android SDK output: out/install/android-release'
