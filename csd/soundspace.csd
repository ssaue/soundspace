<CsoundSynthesizer>

<CsOptions>
-odac -d
</CsOptions>

<CsInstruments>
  sr	    =  44100
  ksmps	    =  10
  nchnls    =  2

  0dbfs	    =  1

  gilisten  OSCinit   8080

turnon 100

instr   100

  Sfile	= ""
  ktag	    	init	0
  kch	    	init	0
  kvol	    	init	0

next:

  kon	    OSClisten	gilisten, "/wavefile/on", "shif", Sfile, ktag, kch, kvol
  koff	    OSClisten	gilisten, "/wavefile/off", "h", ktag

if (kon == 0) goto off

	scoreline {{				;so it sounds like an echo
            i 2  0  3  Sfile, ktag, kch, kvol
            }}, kon

off:
	if (koff == 0) goto done

	turnoff2  101, 4, 1

	kgoto	next  ;Process all events in queue
done:
    endin


instr    101
	Sfile = p4   
	ilen filelen Sfile                 ;length of file
	a1 diskin2 Sfile,1
	kptr init 0
	kptr =    kptr+1    ;increment pointer according to speed and control rate
	if kptr>= ilen then           ;if end of file reached...
		turnoff
	endif

	outch p6, a1
endin   

</CsInstruments>
<CsScore>
f 0 3600  ;Dummy f-table
e
</CsScore>
</CsoundSynthesizer>


/*




<CsoundSynthesizer>
<CsOptions>
-d -m0 -odac
</CsOptions>
<CsInstruments>
sr     = 44100
ksmps  = 64
nchnls = 2
0dbfs  = 1

zakinit   1, 1
gihandle  OSCinit 57112

gapha     init 0
gkspeed   init 1
gkplaying init 0
gidur     = 151   ; duration of the loop (sec)

instr 1
  isamps    = gidur*sr
  gkplaying = 1
  kphs      zkr 1
  iphs      = p4
ptr:
  gapha phasor gkspeed/gidur, iphs
  rireturn
  if (kphs != 0) then
phase:
    iphs = i(kphs) - 1
    rireturn
    reinit phase
    reinit ptr
  endif
  andx = gapha * isamps
  al table3 andx, 1
  ar table3 andx, 2
  out  al, ar
  zkcl 0, 1
endin

instr 2 ; control
  kstatus  init 0
  ksval    init 0
  kpval    init 0
nxtmsg:
  kplay  OSClisten gihandle, "/play",     "i", kstatus
  kspeed OSClisten gihandle, "/speed",    "f", ksval
  kpos   OSClisten gihandle, "/position", "f", kpval

  if (kplay == 0) goto position
  if (kstatus == 1) then
    if (gkplaying != 0) kgoto nxtmsg
    kpha downsamp gapha
    event "i", 1, 0, 36000, kpha
  else
    turnoff2 1,0,0
    gkplaying = 0
  endif
position:
  if (kpos == 0) goto speed
  zkw kpval/gidur + 1, 1
speed:
  if (kspeed == 0) goto ex
  gkspeed = ksval
  kgoto nxtmsg
ex:
endin
</CsInstruments>
<CsScore>
f1 0 8388608 1 "stornello.wav" 0 0 1
f2 0 8388608 1 "stornello.wav" 0 0 2
i2 0 36000
e
</CsScore>
</CsoundSynthesizer>





    instr 1001   ;Simple instrument

  icps	    init      p4
  kvol	    table     $VOL, gicc  ;Read MIDI volume from controller table
  kvol	    =  kvol/127

  aenv     linsegr    0, .003, p5, 0.03, p5 * 0.5, 0.3, 0
  aosc	    oscil     aenv, icps, gisin

	    out	      aosc * kvol
    endin
*/

