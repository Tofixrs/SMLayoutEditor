{
  stdenv,
  pkgs,
  ...
}:
stdenv.mkDerivation rec {
  pname = "SMLayoutEditor-ConfigGen";
  version = "1.0.1";
  src = ../../.;
  nativeBuildInputs = with pkgs; [cmake pkg-config];
  buildInputs = with pkgs; [tinyxml-2];
  meta = {
    mainProgram = pname;
  };
}
