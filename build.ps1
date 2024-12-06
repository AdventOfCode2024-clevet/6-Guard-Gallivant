if (Test-Path -Path "build") {
    Write-Host "Removing existing 'build' folder..."
    Remove-Item -Recurse -Force "build"
}

Write-Host "Creating 'build' folder..."
New-Item -ItemType Directory -Path "build"

Set-Location -Path "build"

Write-Host "Generating build files..."
cmake -G "MinGW Makefiles" ..

Write-Host "Compiling project..."
cmake --build .

Set-Location -Path ..

Write-Host "Build completed."
