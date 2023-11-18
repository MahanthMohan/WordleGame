function compile([string]$outFile) {
    g++ main.cpp -o -SuppressWarnings $outFile
}

function run() {
    compile("keyboard")
    .\keyboard
}

run