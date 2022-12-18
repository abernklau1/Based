# pushd ../

vendor/bin/premake/premake5 gmake2
if [ "$1" == "Editor" ]
then
  make Based-Editor
  bin/Debug-macosx-ARM64/Based-Editor/Based-Editor
elif [ "$1" == "Sandbox" ]
then
  make Sandbox
  bin/Debug-macosx-ARM64/Sandbox/Sandbox
else
  echo "Unknown project"
fi
