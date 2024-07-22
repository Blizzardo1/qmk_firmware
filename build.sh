#!/bin/bash
# Generated online by https://argbash.io/generate

if [[ ! $MSYSTEM ]]; then
    export MSYSTEM=MINGW64
    export MSYS2_PATH_TYPE=inherit
fi

_arg_compile="on"
_arg_flash="on"

_arg_keyboard="keychron"
_arg_model="k10_pro"
_arg_layout="ansi"
_arg_led="rgb"
_arg_keymap="kenobi"
_arg_parallel=8
_arg_generate_compilation_database="off"

compile()
{
    echo "Compiling ${_arg_keyboard}/${_arg_model}/${_arg_layout}/${_arg_led} with \"${_arg_keymap}\" keymap"
    time qmk compile --keyboard ${_arg_keyboard}/${_arg_model}/${_arg_layout}/${_arg_led} --keymap ${_arg_keymap} -j ${_arg_parallel}

	if [[ $? -ne 0 ]]; then
		echo "Compilation failed. Exiting (${$?})"
		exit 1
	fi
	return 0
}

flash()
{
	echo "Flashing Keyboard"
    if [[ $_arg_compile == "off" ]]; then
        echo "Flashing ${_arg_keyboard}/${_arg_model}/${_arg_layout}/${_arg_led} with \"${_arg_keymap}\" keymap"
        time qmk flash "${_arg_keyboard}_${_arg_model}_${_arg_layout}_${_arg_led}_${_arg_keymap}.bin"
    elif [[ $_arg_compile == "on" ]]; then
        echo "Compiling and Flashing ${_arg_keyboard}/${_arg_model}/${_arg_layout}/${_arg_led} with \"${_arg_keymap}\" keymap"
        time qmk flash --keyboard ${_arg_keyboard}/${_arg_model}/${_arg_layout}/${_arg_led} --keymap ${_arg_keymap} -j ${_arg_parallel}
    fi

	if [[ $? -ne 0 ]]; then
		echo "Could not flash Keyboard! Exiting (${$?})"
		exit 1
	fi
	return 0
}

die()
{
	local _ret="${2:-1}"
	test "${_PRINT_HELP:-no}" = yes && print_help >&2
	echo "$1" >&2
	exit "${_ret}"
}


begins_with_short_option()
{
	local first_option all_short_options='gcfkmldeph'
	first_option="${1:0:1}"
	test "$all_short_options" = "${all_short_options/$first_option/}" && return 1 || return 0
}

print_help()
{
	printf '%s\n' "Help with Kenobi's Build Script"
	printf 'Usage: %s [-c|--(no-)compile] [-f|--(no-)flash] [-h|--help]\n' "$0"
	printf '\t%s\n' "-c, --compile, --no-compile: compile firmware (on by default)"
	printf '\t%s\n' "-f, --flash, --no-flash: flash firmware to keyboard (on by default)"
    printf '\t%s\n' "-g, --generate-compilation-database: generate compilation database"
    printf '\t%s\n' "-k, --keyboard: keyboard name"
    printf '\t%s\n' "-m, --model: keyboard model"
    printf '\t%s\n' "-l, --layout: keyboard layout"
    printf '\t%s\n' "-d, --led: keyboard led"
    printf '\t%s\n' "-e, --keymap: keyboard keymap"
    printf '\t%s\n' "-p, --parallel: number of parallel jobs"
	printf '\t%s\n' "-h, --help: Prints help"
}


parse_commandline()
{
	while test $# -gt 0
	do
		_key="$1"
		case "$_key" in
            -g|--generate-compilation-database)
                _arg_generate_compilation_database="on"
                ;;
            -g*)
                _arg_generate_compilation_database="on"
                _next="${_key##-g}"
                if test -n "$_next" -a "$_next" != "$_key"
                then
                    { begins_with_short_option "$_next" && shift && set -- "-g" "-${_next}" "$@"; } || die "The short option '$_key' can't be decomposed to ${_key:0:2} and -${_key:2}, because ${_key:0:2} doesn't accept value and '-${_key:2:1}' doesn't correspond to a short option."
                fi
                ;;
			-c|--no-compile|--compile)
				_arg_compile="on"
				test "${1:0:5}" = "--no-" && _arg_compile="off"
				;;
			-c*)
				_arg_compile="on"
				_next="${_key##-c}"
				if test -n "$_next" -a "$_next" != "$_key"
				then
					{ begins_with_short_option "$_next" && shift && set -- "-c" "-${_next}" "$@"; } || die "The short option '$_key' can't be decomposed to ${_key:0:2} and -${_key:2}, because ${_key:0:2} doesn't accept value and '-${_key:2:1}' doesn't correspond to a short option."
				fi
				;;
			-f|--no-flash|--flash)
				_arg_flash="on"
				test "${1:0:5}" = "--no-" && _arg_flash="off"
				;;
			-f*)
				_arg_flash="on"
				_next="${_key##-f}"
				if test -n "$_next" -a "$_next" != "$_key"
				then
					{ begins_with_short_option "$_next" && shift && set -- "-f" "-${_next}" "$@"; } || die "The short option '$_key' can't be decomposed to ${_key:0:2} and -${_key:2}, because ${_key:0:2} doesn't accept value and '-${_key:2:1}' doesn't correspond to a short option."
				fi
				;;
			-k|--keyboard)
				test $# -lt 2 && die "Missing value for the optional argument '$_key'." 1
				_arg_keyboard="$2"
				shift
				;;
			--keyboard=*)
				_arg_keyboard="${_key##--keyboard=}"
				;;
			-k*)
				_arg_keyboard="${_key##-k}"
				;;
			-m|--model)
				test $# -lt 2 && die "Missing value for the optional argument '$_key'." 1
				_arg_model="$2"
				shift
				;;
			--model=*)
				_arg_model="${_key##--model=}"
				;;
			-m*)
				_arg_model="${_key##-m}"
				;;
			-l|--layout)
				test $# -lt 2 && die "Missing value for the optional argument '$_key'." 1
				_arg_layout="$2"
				shift
				;;
			--layout=*)
				_arg_layout="${_key##--layout=}"
				;;
			-l*)
				_arg_layout="${_key##-l}"
				;;
			-d|--led)
				test $# -lt 2 && die "Missing value for the optional argument '$_key'." 1
				_arg_led="$2"
				shift
				;;
			--led=*)
				_arg_led="${_key##--led=}"
				;;
			-d*)
				_arg_led="${_key##-d}"
				;;
			-e|--keymap)
				test $# -lt 2 && die "Missing value for the optional argument '$_key'." 1
				_arg_keymap="$2"
				shift
				;;
			--keymap=*)
				_arg_keymap="${_key##--keymap=}"
				;;
			-e*)
				_arg_keymap="${_key##-e}"
				;;
			-p|--parallel)
				test $# -lt 2 && die "Missing value for the optional argument '$_key'." 1
				_arg_parallel="$2"
				shift
				;;
			--parallel=*)
				_arg_parallel="${_key##--parallel=}"
				;;
			-p*)
				_arg_parallel="${_key##-p}"
				;;
			-h|--help)
				print_help
				exit 0
				;;
			-h*)
				print_help
				exit 0
				;;
			*)
				_PRINT_HELP=yes die "FATAL ERROR: Got an unexpected argument '$1'" 1
				;;
		esac
		shift
	done
}


parse_commandline "$@"

if [[ $_arg_generate_compilation_database == "on" ]]; then
    echo "Generating Compilation Database"
    qmk generate-compilation-database --keyboard "${_arg_keyboard}/${_arg_model}/${_arg_layout}/${_arg_led}" --keymap "${_arg_keymap}"
fi

if [[ $_arg_compile == "on" && $_arg_flash == "off" ]]; then
    compile
elif [[ $_arg_flash == "on" ]]; then
    flash
fi

die "Complete! Enjoy your new firmware!"
