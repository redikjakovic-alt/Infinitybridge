param(
    [Parameter(Mandatory = $true)]
    [string]$XexPath,

    [Parameter(Mandatory = $true)]
    [string]$XexToolPath,

    [string]$OutputDirectory = ".\xex-inspection"
)

$ErrorActionPreference = "Stop"

$xex = (Resolve-Path -LiteralPath $XexPath).Path
$xexTool = (Resolve-Path -LiteralPath $XexToolPath).Path
$outDir = [System.IO.Path]::GetFullPath($OutputDirectory)

if (-not (Test-Path -LiteralPath $xex -PathType Leaf)) {
    throw "XEX file not found: $xex"
}
if (-not (Test-Path -LiteralPath $xexTool -PathType Leaf)) {
    throw "XexTool not found: $xexTool"
}

New-Item -ItemType Directory -Force -Path $outDir | Out-Null

# Work on a copy so the source file is never passed to the inspection tool.
$workingCopy = Join-Path $outDir "default_copy.xex"
$baseFile = Join-Path $outDir "default_basefile.bin"
$idcFile = Join-Path $outDir "default.idc"

Copy-Item -LiteralPath $xex -Destination $workingCopy -Force

Write-Host "Inspecting a copy of: $xex"
Write-Host "Output directory: $outDir"

# -b extracts the basefile; -i writes an IDC description.
# No patching, re-encryption, or modification options are used.
& $xexTool -b $baseFile -i $idcFile $workingCopy
if ($LASTEXITCODE -ne 0) {
    throw "XexTool failed with exit code $LASTEXITCODE"
}

Write-Host ""
Write-Host "Inspection files:"
Get-Item -LiteralPath $workingCopy, $baseFile, $idcFile |
    Select-Object Name, Length, FullName |
    Format-Table -AutoSize

Write-Host ""
Write-Host "Potential raw-input / XInput references in IDC:"
Select-String -LiteralPath $idcFile -Pattern "Beyond|XInput|SetupImport" |
    ForEach-Object { $_.Line }

Write-Host ""
Write-Host "No game file was patched. Keep default_copy.xex and default_basefile.bin unchanged."
Write-Host "For the first review, send default.idc and the original default.xex."
