{
  stdenv,
  pkgs,
  ...
}:
stdenv.mkDerivation rec {
  pname = "SMLayoutEditor-ConfigGen";
  version = "0.0.1";
  src = ../../.;
  nativeBuildInputs = with pkgs; [cmake pkg-config];
  buildInputs = with pkgs; [tinyxml-2];
  meta = {
    mainProgram = pname;
  };
}
