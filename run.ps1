cmake -B build
if ($LASTEXITCODE -ne 0) { exit 1 }

cmake --build build
if ($LASTEXITCODE -ne 0) { exit 1 }

if (Test-Path .\build\Debug\MonJeu.exe) {
    .\build\Debug\MonJeu.exe
} else {
    .\build\MonJeu.exe
}