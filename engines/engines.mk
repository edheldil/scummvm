ifdef ENABLE_SCUMM
DEFINES += -DENABLE_SCUMM=$(ENABLE_SCUMM)
MODULES += engines/scumm

ifdef ENABLE_SCUMM_7_8
DEFINES += -DENABLE_SCUMM_7_8
endif

ifdef ENABLE_HE
DEFINES += -DENABLE_HE
endif

endif

ifdef ENABLE_AGI
DEFINES += -DENABLE_AGI=$(ENABLE_AGI)
MODULES += engines/agi
endif

ifdef ENABLE_AGOS
DEFINES += -DENABLE_AGOS=$(ENABLE_AGOS)
MODULES += engines/agos
endif

ifdef ENABLE_CINE
DEFINES += -DENABLE_CINE=$(ENABLE_CINE)
MODULES += engines/cine
endif

ifdef ENABLE_CRUISE
DEFINES += -DENABLE_CRUISE=$(ENABLE_CRUISE)
MODULES += engines/cruise
endif

ifdef ENABLE_DRASCULA
DEFINES += -DENABLE_DRASCULA=$(ENABLE_DRASCULA)
MODULES += engines/drascula
endif

ifdef ENABLE_GOB
DEFINES += -DENABLE_GOB=$(ENABLE_GOB)
MODULES += engines/gob
endif

ifdef ENABLE_GROOVIE
DEFINES += -DENABLE_GROOVIE=$(ENABLE_GROOVIE)
MODULES += engines/groovie
endif

ifdef ENABLE_IGOR
DEFINES += -DENABLE_IGOR=$(ENABLE_IGOR)
MODULES += engines/igor
endif

ifdef ENABLE_KYRA
DEFINES += -DENABLE_KYRA=$(ENABLE_KYRA)
MODULES += engines/kyra
endif

ifdef ENABLE_LURE
DEFINES += -DENABLE_LURE=$(ENABLE_LURE)
MODULES += engines/lure
endif

ifdef ENABLE_M4
DEFINES += -DENABLE_M4=$(ENABLE_M4)
MODULES += engines/m4
endif

ifdef ENABLE_MADE
DEFINES += -DENABLE_MADE=$(ENABLE_MADE)
MODULES += engines/made
endif

ifdef ENABLE_PARALLACTION
DEFINES += -DENABLE_PARALLACTION=$(ENABLE_PARALLACTION)
MODULES += engines/parallaction
endif

ifdef ENABLE_QUEEN
DEFINES += -DENABLE_QUEEN=$(ENABLE_QUEEN)
MODULES += engines/queen
endif

ifdef ENABLE_SAGA
DEFINES += -DENABLE_SAGA=$(ENABLE_SAGA)
MODULES += engines/saga

ifdef ENABLE_IHNM
DEFINES += -DENABLE_IHNM
endif

ifdef ENABLE_SAGA2
DEFINES += -DENABLE_SAGA2
endif

endif

ifdef ENABLE_SCI
DEFINES += -DENABLE_SCI=$(ENABLE_SCI)
MODULES += engines/sci
endif

ifdef ENABLE_SKY
DEFINES += -DENABLE_SKY=$(ENABLE_SKY)
MODULES += engines/sky
endif

ifdef ENABLE_SWORD1
DEFINES += -DENABLE_SWORD1=$(ENABLE_SWORD1)
MODULES += engines/sword1
endif

ifdef ENABLE_SWORD2
DEFINES += -DENABLE_SWORD2=$(ENABLE_SWORD2)
MODULES += engines/sword2
endif

ifdef ENABLE_TINSEL
DEFINES += -DENABLE_TINSEL=$(ENABLE_TINSEL)
MODULES += engines/tinsel
endif

ifdef ENABLE_TOUCHE
DEFINES += -DENABLE_TOUCHE=$(ENABLE_TOUCHE)
MODULES += engines/touche
endif

ifdef ENABLE_TUCKER
DEFINES += -DENABLE_TUCKER=$(ENABLE_TUCKER)
MODULES += engines/tucker
endif
