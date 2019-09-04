TAG=test_201909030410
YEAR2016=hists/WWW3L2016_v5.2.1/${TAG}
YEAR2017=hists/WWW3L2017_v5.2.1/${TAG}
YEAR2018=hists/WWW3L2018_v5.2.1/${TAG}

YEARCOMB=hists/combineyears3L_v5.2.1/${TAG}

if [ ! -d "$YEARCOMB" ]; then
    echo "making dir $YEARCOMB"
    mkdir -p "$YEARCOMB"
fi

find "$YEAR2016" -maxdepth 1 -type f -name '*.root' -printf '%f\n' | while read line; do
    if [ ! -f "$YEAR2016/$line" ]; then
        echo "File $YEAR2016/$line does not exist. continue."
        continue
    fi
    if [ ! -f "$YEAR2017/$line" ]; then
        echo "File $YEAR2017/$line does not exist. continue."
        continue
    fi
    if [ ! -f "$YEAR2018/$line" ]; then
        echo "File $YEAR2018/$line does not exist. continue."
        continue
    fi
    echo "hadd -f $YEARCOMB/$line $YEAR2016/$line $YEAR2017/$line $YEAR2018/$line"
    hadd -f $YEARCOMB/$line $YEAR2016/$line $YEAR2017/$line $YEAR2018/$line &
done

wait
