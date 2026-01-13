[Setup]
AppName=Maitreya8
AppVersion=8.0
DefaultDirName={autopf}\Maitreya8
DefaultGroupName=Maitreya8
UninstallDisplayIcon={app}\maitreya8.exe
Compression=lzma2/ultra64
SolidCompression=yes
OutputDir=installers
OutputBaseFilename=Maitreya8_Setup
ArchitecturesAllowed=x64
ArchitecturesInstallIn64BitMode=x64

[Files]
; Main executable
Source: "release_v8\maitreya8.exe"; DestDir: "{app}"; Flags: ignoreversion

; Resource folders
Source: "release_v8\resources\*"; DestDir: "{app}\resources"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "release_v8\pics\*"; DestDir: "{app}\pics"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "release_v8\fonts\*"; DestDir: "{app}\fonts"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "release_v8\de\*"; DestDir: "{app}\de"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "release_v8\fr\*"; DestDir: "{app}\fr"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "release_v8\hu\*"; DestDir: "{app}\hu"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "release_v8\it\*"; DestDir: "{app}\it"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "release_v8\pl\*"; DestDir: "{app}\pl"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "release_v8\ro\*"; DestDir: "{app}\ro"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "release_v8\ru\*"; DestDir: "{app}\ru"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "release_v8\ta\*"; DestDir: "{app}\ta"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "release_v8\te\*"; DestDir: "{app}\te"; Flags: ignoreversion recursesubdirs createallsubdirs

; Other files
Source: "release_v8\geonames1000.sql"; DestDir: "{app}"; Flags: ignoreversion
Source: "release_v8\Copying.txt"; DestDir: "{app}"; Flags: ignoreversion
Source: "release_v8\maitreya8.pot"; DestDir: "{app}"; Flags: ignoreversion
Source: "release_v8\maitreya8.ico"; DestDir: "{app}"; Flags: ignoreversion

[Icons]
Name: "{group}\Maitreya8"; Filename: "{app}\maitreya8.exe"; IconFilename: "{app}\maitreya8.ico"
Name: "{group}\Uninstall Maitreya8"; Filename: "{uninstallexe}"
Name: "{commondesktop}\Maitreya8"; Filename: "{app}\maitreya8.exe"; Tasks: desktopicon; IconFilename: "{app}\maitreya8.ico"

[Tasks]
Name: "desktopicon"; Description: "Create a &desktop icon"; GroupDescription: "Additional icons:"; Flags: unchecked

[Run]
Filename: "{app}\maitreya8.exe"; Description: "Launch Maitreya8"; Flags: nowait postinstall skipifsilent
