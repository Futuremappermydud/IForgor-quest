Param(
    [String]$qmodname="",
    [Parameter(Mandatory=$false)]
    [Switch]$clean
)

if ($qmodName -eq "")
{
    Write-Output "Give a proper qmod name and try again"
    exit
}
$mod = "./mod.json"
$modJson = Get-Content $mod -Raw | ConvertFrom-Json

$filelist = @($mod)

$cover = "./" + $modJson.coverImage
if ((-not ($cover -eq "./")) -and (Test-Path $cover))
{
    $filelist += ,$cover
}

foreach ($mod in $modJson.modFiles)
{
        $path = "./build/" + $mod
    if (-not (Test-Path $path))
    {
        $path = "./extern/libs/" + $mod
    }
    $filelist += $path
}

foreach ($lib in $modJson.libraryFiles)
{
    $path = "./extern/libs/" + $lib
    if (-not (Test-Path $path))
    {
        $path = "./build/" + $lib
    }
    Write-Output $path
    $filelist += $path
}

$zip = $qmodName + ".zip"
$qmod = $qmodName + ".qmod"

if ((-not ($clean.IsPresent)) -and (Test-Path $qmod))
{
    Write-Output "Making Clean Qmod"
    Move-Item $qmod $zip -Force
}

Compress-Archive -Path $filelist -DestinationPath $zip -Update
Move-Item $zip $qmod -Force