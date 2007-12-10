#!/bin/bash
# Bash wrapper to interact with ASInstallInterface (asinsfaz)


function initAifaz() {

  poof2&
  DPID=poof2-$!
  while [ -z "$PFID" ]
  do
    
    echo "Waiting for DPID"
    PFID=$(dcop|grep $DPID)
    sleep 1
  done
  sleep 1
  export DPID=$DPID
  echo "ASINFAZ running..";
}

function endAifaz() {
   dcop $DPID MainApplication-Interface quit

}

function getFile () {

  INISTAT=$(dcop $DPID dcoper getFile $1 $2)
  if [ "$INITSTAT" = "-1" ]
  then
    echo "Error dowloading file $1"
    echo "Error code:" $(dcop $DPID dcoper getStatus)
    exit 1
  fi
  STATUS=$(dcop $DPID dcoper getStatus)
  while [ "$STATUS" != "0" ]
  do
    if [ -z "$STATUS" ]
    then
       echo "Connection broken ($STATUS)";
       return -1
    fi
    echo -e -n "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\bStill downloading ($STATUS)  ";
    sleep 2
    STATUS=$(dcop $DPID dcoper getStatus)
  done
  ERRSTATUS=$(dcop $DPID dcoper errStatus)
  if [ "$ERRSTATUS" = "0" ]
  then
    echo "Download complete : $ERRSTATUS";
    return 0
  else
    echo "Download incomplete : $ERRSTATUS";
    return -1
  fi
  
}




function setSay ()  {
  dcop $DPID dcoper setSay "$*"
}

function setShot () {
 dcop $DPID dcoper setShot "$*"
}

function setLabel () {

 dcop $DPID dcoper setLabel "$*"

}

function setProgreso () {

 dcop $DPID dcoper setProgreso "$*"

}

function setProgresoP () {

 dcop $DPID dcoper setProgresoP "$*"

}

function showAifaz () {

 dcop $DPID dcoper shoshow 

}

function setTitle () {

 dcop $DPID dcoper setTitle "$*" 

}
