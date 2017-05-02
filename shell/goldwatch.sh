#!/bin/sh
# ************************************************************************************************
#                     Licensed under the Academic Free License version 3.0
#                                   Written by Ali Muhammed
#                                   patrash.ali@promwad.com
#                                     uniapi@outlook.com
#                                       March 27, 2017
# ************************************************************************************************

# handler for SIGINT and SIGTERM
off() {
    rc                                          # resetting colors
    clear                                       # clearing to fill the screen
	exit 0
}

# diagnostic messaging while escaping
esc() {
    for i; do
        echo -n "$i"
    done
    exit 1
}

# read-only variables for setting colors
readonly BLACK=0
readonly RED=1
readonly GREEN=2
readonly YELLOW=3
readonly BLUE=4
readonly PURPLE=5
readonly CYAN=6
readonly WHITE=7

# resetting screen colors
rc() {
    echo -n "\033[0m"
}

# setting foreground colors
# params: COLOR [LIGHT]
fc() {
    if [ $# -eq 2 ]; then                       # if a user specifies an argument
        LIGHT=$2                                # setting to whatever the user want
    else
        LIGHT=1                                 # default is light
    fi
    echo -n "\033[$LIGHT;$(($1+30))m"
}

# wrappers
red() {
    fc $RED
}
green() {
    fc $GREEN
}
yellow() {
    fc $YELLOW
}
blue() {
    fc $BLUE
}
purple() {
    fc $PURPLE
}
cyan() {
    fc $CYAN
}
white() {
    fc $WHITE
}

# printing error messages to stderr
error() {
    echo -n "$(red)error: $(rc)" >& 2
    echo " $@" >& 2
}

# printing error messages while connecting
netless() {
    ERROR=
    TIP="check the internet connection"
    if [ $SCLR -ne 0 ]; then                    # if the currency table needs clearing
        rc
        clear
        ERROR="connection lost: "
    fi
    if [ $1 -eq 1 ]; then
        ERROR="$(echo "$ERROR")inappropriate web response"
    elif [ $1 -eq 4 ]; then
        ERROR="$(echo "$ERROR")irresolvable host address"
    elif [ $1 -eq 8 ]; then
        ERROR="$(echo "$ERROR")web not found"
        TIP="try to contact the support team"
    fi
    esc $(error "$ERROR") $(tip "$TIP")
}

# printing tip messages to stdout
tip () {
	echo "$(cyan)tip:$(rc) $1" >& 2
    if [ $# -gt 1 ]; then
        i=0
        while [ $i -le $# ]; do
            shift
            echo "     $1" >& 2
            i=$(($i+1))
        done
    fi
	rc
}

# background of the currency table
ground() {
    printf "\033[27;1;37;40m"
}

# background of goldwatch.sh
space() {
    printf "\033[1;37;40;7m\n"
    printf "%s" "$@"
}

# operator for testing two floating-point numbers as POSIX shell has no built-in logic for comparing floats
float() {
    Xi=$(echo $1 | grep -Po "^[0-9]*")          # getting an integer part for the first float
    Yi=$(echo $3 | grep -Po "^[0-9]*")          # getting an integer part for the second float
    if [ -z $Xi ]; then                         # if the integer part of the first float is empty
        Xi=0
    fi
    if [ -z $Yi ]; then                         # if the integer part of the second float is empty
        Yi=0
    fi
    if [ $Xi -ne $Yi ]; then                    # if the integer parts are not equal there's no need to test the floating parts
        if test $Xi $2 $Yi; then                # testing the integer parts
            return 0
        else
            return 1
        fi
    else
        Xf=$(echo $1 | grep -Po "[0-9]*$")      # getting a floating part for the first float
        Yf=$(echo $3 | grep -Po "[0-9]*$")      # getting a floating part for the second float
        if [ -z $Xf ]; then                     # if the floating part of the first float is empty
            Xf=0
        fi
        if [ -z $Yf ]; then                     # if the floating part of the second float is empty
            Yf=0
        fi
        test $Xf $2 $Yf                         # testing the floating parts
        return $?
    fi
}

# constructing string-like-arrays as POSIX shell has no built-in arrays
array() {
	spc=										# declaring a local SPC variable which is empty
	if [ $# -ge 1 ] && [ $1 = '-s' ]; then      # checking if -s is set for adding extra characters
		if [ $# -ge 2 ]; then                   # checking if there's a param for -s
			spc="$2"                            # saving characters for insertion
			shift 2                             # skipping optional params and shifting to args
		else
			shift                               # skipping optional -s to exclude it while iterating
		fi
	fi
	for i in $@; do                             # iterating through the args
		printf '%s%s\n' "$spc" "$i"             # printing to stdout so use redirecting to the desired target
	done
    return 0
}

# getting an indexed entry of the string-like-array
# the index starting from one
# params: array index
geti() {
    if [ $# -ne 2 ]; then
        return 1
    fi
    N=`echo "$1" | wc -l`
    echo "$2" | grep -qP ^[0-9]+                # validating an index
    if [ $? -ne 0 ]; then                       # if the index is not valid
        return 3
    elif [ $N -lt $2 ]; then                    # if the index exceeds the range
        return 4
    fi
    N=`echo $2p`                                # preparing a pattern for an element extaction
    echo "$1" | sed -n $N                       # extracting and printing the element
    return 0
}

# getting element occurences in the array
# params: array element
getx() {
    if [ $# -ne 2 ]; then                       # if there are two params
        return 1
    fi
    echo "$1" | grep -P "$2"                    # occurence of the second in the first
    if [ $? -ne 0 ]; then                       # if there is not
        return 2
    fi
    return 0
}

PROG="$0"                                       # an absolute path to this executable
CONFI="config.ini"
CONFS="${PROG%/*}/$CONFI"                       # a location of config.ini for accessing from anywhere
                                                                                    # available currency
ALLCRCY=$(array "-s" "        " "USD" "AED" "AUD" "BHD" "BRL" "CAD" "CNY" "EGP" "EUR" "GPB" "HKD" "IDR" "INR" "KWD" "RUB" "SAR" "JPY")

readonly TIMEOUT=9                                                                  # the timeout for requests
readonly WEB="http://goldprice.org"                                                 # the main web page address
readonly API="http://data-asg.goldprice.org/GetData/"		                        # the web address for HTTP-GET requests
readonly PJOBJ="var\s+\w+\s*=\s*\{\s*(['\"]?\w+['\"]?\s*:\s*[-+,.:'\"\/\w\s]+)\};"  # the json objects declaration pattern
readonly PURL="\bhttps?:\/\/[-\w.\/*\.[a-z]{2,10}"	                                # the http(s) urls pattern
readonly PCRCY="^[A-Z]{3}$"                                                         # the currency pattern
readonly PCYCLE="^[0-9]*$"                                                          # the cycle period pattern
                                                                                    # the json data curreny object pattern
readonly PJCXA="^\[\s*['\"]?[A-Z]{3}-[A-Z]{3}['\"]?\s*[:,]\s*['\"]?\d+\.?\d*['\"]?\s*\]$"

SCLR=0                                          # the flag for clearing the screen
PAGE=                                           # the main page
CYCLE=0                                         # a cycle period
CRCY=                                           # a currency
CXU=0                                           # a currency for gold
CXG=0                                           # a currency for silver
SCXU=0                                          # statistics for gold
SCXG=0                                          # statistics for silver
SPACE="    "                                    # space to fill starting from the left of the currency table
OPC=0                                           # an operation code
# initializing configuration:
# trying to open config.ini, validating formats
# reading a CYCLE period and a C(UR)R(EN)CY notation
confini() {
	opc=0
    if [ ! -e "$CONFS" ]; then                  # if config.ini does not exist
        error "config.ini not found"
	    return 1
    fi
    len=$(wc -l "$CONFS" | grep -Po "^\d+")     # counting the length of config.ini
    if [ $len -gt 2 ] || [ $len -lt 1 ]; then   # if the file format has more than two lines or less than one
        error "bad file format"
	    opc=2
    elif [ $len -eq 2 ]; then                   # if the format has two lines
        grep -Pzq "^\d+\s*[A-Z]{3}$" "$CONFS"   # validating the configuration format
        if [ $? -ne 0 ]; then                   # if it's not valid
            error "bad config format"
            opc=3
        else
            CRCY=$(grep -P "$PCRCY" "$CONFS")   # reading the currency
        fi
    else
         opc=0                                  # default settings
         CRCY="USD"                             # setting to default if the format has one line
    fi
    if [ $opc -eq 0 ]; then                     # if there's need to continue
        CYCLE=$(grep "$PCYCLE" "$CONFS")        # reading the cycle period
        if [ -z $CYCLE ]; then                  # if the cycle period is empty
            error "bad config format"
            opc=3
        else
            n=$(getx "$ALLCRCY" "$CRCY")        # getting for being available
            if [ $? -ne 0 ]; then
                error "unavailable currency"
                opc=4
            fi
        fi
    fi
    return $opc
}

# preparations before the main routine
ini() {
    trap "off" INT TERM                         # setting a handler for SIGINT and SIGTERM

    confini                                     # initializing configurations
    OPC=$?
    if [ $OPC -ne 0 ]; then                     # if unsuccessful
        if [ $OPC -eq 1 ]; then                 # the code status: not found
            tip "echo n > $CONFI" "cp $CONFI path" \
                "where n is count in sec" \
                "path is a location of ${PROG##*/}"
            exit $OPC
        elif [ $OPC -eq 2 ]; then               # the code status: bad file format
            tip "$CONFI should contain only one or two lines" "SECONDS - an integer update rate" \
                "[CURRENCY] - an optional currency code, USD by default"
            exit $OPC
        elif [ $OPC -eq 3 ]; then               # the code status: bad config format
            tip "the conventional config format:" "SECONDS - an integer update rate" \
                "[CURRENCY] - an optional currency code, USD by default"
            exit $OPC
        elif [ $OPC -eq 4 ]; then               # the code status: unavailable currency
            tip "available currency notations:"
            echo "$SPACE" $ALLCRCY              # double quotes are left intentionally
            exit $OPC
        fi
    fi
    return 0
}

# requesting a currency json data
# params: XAU | XAG
rxa() {
    RQXA=$(printf '%s%s-%s/1' "$API" "$CRCY" "$1")        # preparing a currency request
    JCRCY=$(wget -qO- "$RQXA" --timeout=$TIMEOUT)         # downloading the currency json data
    OPC=$?                                                # saving the status code
    if [ $OPC -ne 0 ]; then                               # if unsuccessful
        return $OPC
    fi

    JO=`echo "$JCRCY" | grep -Pzo "$PJCXA"`               # validating the json data currency object
    OPC=$?
    if [ $OPC -ne 0 ]; then                               # if invalid
        return $OPC
    fi

    printf "%2.f" $(echo "$JCRCY" | grep -Po "\d+.?\d*")  # extracting and printing the currency
    return 0
}

# saving statistics for gold and silver
sxa() {
    SCXU=`rxa XAU`                                        # requesting and saving for a further gold statistics
    OPC=$?
    if [ $OPC -ne 0 ]; then
        return $OPC
    fi
    SCXG=`rxa XAG`                                        # requesting and saving for a further silver statistics
    OPC=$?
    if [ $OPC -ne 0 ]; then
        return $OPC
    fi
}

# detecting ups and downs of the currency
cxa() {
    scx=                                        # a storage for SXCU or SXCG
    cx=                                         # a storage for CXU of CXG
    case $1 in
        CXU )                                   # a gold option
            scx=$SCXU
            cx=$CXU
        ;;
        CXG )                                   # a silver option
            scx=$SCXG
            cx=$CXG
        ;;
        * ) error "\"$1\" - unrecognized options"
            return 1
    esac

    if float $scx -lt $cx; then                 # if ups
        fc $RED
    elif float $scx '-gt' $cx; then             # if downs
        fc $GREEN
    else
        fc $WHITE
    fi
    printf "%13.2f" $cx
    white
}

# the currency table
crcy() {
    clear
    echo -n "$SPACE$SPACE $SPACE $WEB (R)"
    echo -n "\n$(ground)"
    echo -n "$(space "$SPACE" `ground`)  ________________________________________  "
    echo -n "$(space "$SPACE" `ground`) |          |              |              | "
    echo -n "$(space "$SPACE" `ground`) | `purple`Currency`white` |     `yellow`Gold`white`     |    `fc $WHITE 0`Silver`white`    | "
    echo -n "$(space "$SPACE" `ground`) |__________|______________|______________| "
    echo -n "$(space "$SPACE" `ground`) |          |              |              | "
    echo -n "$(space "$SPACE" `ground`) |    `cyan`$CRCY`white`   |`cxa CXU` |`cxa CXG` | "
    echo -n "$(space "$SPACE" `ground`) |__________|______________|______________| "
    echo -n "$(space "$SPACE" `ground`)                                            "
    echo -n "$(space)\n\n$SPACE  Updated: `date +%c`\n\n$USER$ "

    return 0
}

ini                                                 # preparations before the main routine
echo -n "connecting..."
sxa                                                 # saving for a further statistics
OPC=$?
if [ $OPC -ne 0 ]; then                             # if unsuccessful statistics saving
    echo ""
    netless $OPC
    exit
fi

space                                               # setting a default color for goldwatch.sh
clear                                               # clearing to fill the screen
SCLR=1
renice 19 -p $$ > /dev/null                         # changing the priority to let the system do tasks a bit faster

# the main routine
while [ 1 ]; do

    xu=`rxa XAU`                                    # requesting the gold currency
    OPC=$?
    if [ $OPC -ne 0 ]; then
        netless $OPC
        exit 1
    fi

    xg=`rxa XAG`                                    # requesting the silver currency
    OPC=$?
    if [ $OPC -ne 0 ]; then                         # if the response is inappropriate
        netless $OPC
        exit 1
    fi

    if [ ! $xu = $CXU ] || [ ! $xg = $CXG ]; then   # if the data in the table should be changed
        CXU=$xu
        CXG=$xg

        crcy                                        # displaying the currency table
    fi

	sleep $CYCLE                                    # waiting for the next cycle period to continue
done
