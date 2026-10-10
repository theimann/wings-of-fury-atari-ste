# Sourced by the scripts in tools/ and game/: where things are on this machine. Every value can be set in the
# environment or in local.env in the repository's root (not in git); the defaults are:
#   AGTROOT      ../agtools beside the repository: AGT with agt-patch/agtools-local.patch applied
#   CROSS_MINT   $HOME/cross-mint if it exists (the m68k-atari-mint toolchain; AGT's own default is /opt/cross-mint)
#   PYTHON       .venv/bin/python in the repository if it exists, else python3 (needs Pillow)
#   WOF_BUILDS   builds/ in the repository: where tools/make_release.sh puts the releases
#   HATARI       hatari on the PATH, else the macOS application
#   WOF_TOS      the TOS image Hatari boots (no default: TOS 1.62 or 2.06, not part of this repository)
WOF_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
[ -f "$WOF_ROOT/local.env" ] && . "$WOF_ROOT/local.env"
: "${AGTROOT:=$WOF_ROOT/../agtools}"
if [ -z "${CROSS_MINT:-}" ] && [ -d "$HOME/cross-mint/bin" ]; then CROSS_MINT="$HOME/cross-mint"; fi
[ -n "${CROSS_MINT:-}" ] && PATH="$CROSS_MINT/bin:$PATH"
if [ -z "${PYTHON:-}" ]; then
  if [ -x "$WOF_ROOT/.venv/bin/python" ]; then PYTHON="$WOF_ROOT/.venv/bin/python"
  elif [ -x "$WOF_ROOT/../tools/venv/bin/python" ]; then PYTHON="$WOF_ROOT/../tools/venv/bin/python"
  else PYTHON=python3; fi
fi
: "${WOF_BUILDS:=$WOF_ROOT/builds}"
if [ -z "${HATARI:-}" ]; then
  if command -v hatari > /dev/null 2>&1; then HATARI=hatari; else HATARI=/Applications/Hatari.app/Contents/MacOS/hatari; fi
fi
export WOF_ROOT AGTROOT CROSS_MINT PYTHON WOF_BUILDS HATARI WOF_TOS PATH
