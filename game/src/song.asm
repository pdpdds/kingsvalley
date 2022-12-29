; ALIENALL, Song part, encoded in the AKM (minimalist) format V0.


ALIENALL_Start
ALIENALL_StartDisarkGenerateExternalLabel

ALIENALL_DisarkPointerRegionStart0
	dw ALIENALL_InstrumentIndexes	; Index table for the Instruments.
	dw ALIENALL_ArpeggioIndexes - 2	; Index table for the Arpeggios.
ALIENALL_DisarkForceNonReferenceDuring2_1
	dw 0	; Index table for the Pitches.

; The subsongs references.
	dw ALIENALL_Subsong0
	dw ALIENALL_Subsong1
ALIENALL_DisarkPointerRegionEnd0

; The Instrument indexes.
ALIENALL_InstrumentIndexes
ALIENALL_DisarkPointerRegionStart2
	dw ALIENALL_Instrument0
	dw ALIENALL_Instrument1
	dw ALIENALL_Instrument2
	dw ALIENALL_Instrument3
	dw ALIENALL_Instrument4
	dw ALIENALL_Instrument5
	dw ALIENALL_Instrument6
	dw ALIENALL_Instrument7
	dw ALIENALL_Instrument8
	dw ALIENALL_Instrument9
ALIENALL_DisarkPointerRegionEnd2

; The Instrument.
ALIENALL_DisarkByteRegionStart3
ALIENALL_Instrument0
	db 255	; Speed.

ALIENALL_Instrument0Loop	db 0	; Volume: 0.

	db 4	; End the instrument.
ALIENALL_DisarkPointerRegionStart4
	dw ALIENALL_Instrument0Loop	; Loops.
ALIENALL_DisarkPointerRegionEnd4

ALIENALL_Instrument1
	db 0	; Speed.

	db 61	; Volume: 15.

	db 61	; Volume: 15.

	db 57	; Volume: 14.

	db 57	; Volume: 14.

	db 53	; Volume: 13.

	db 53	; Volume: 13.

	db 49	; Volume: 12.

	db 49	; Volume: 12.

	db 45	; Volume: 11.

	db 45	; Volume: 11.

	db 41	; Volume: 10.

	db 41	; Volume: 10.

	db 37	; Volume: 9.

	db 37	; Volume: 9.

	db 33	; Volume: 8.

	db 33	; Volume: 8.

	db 29	; Volume: 7.

	db 29	; Volume: 7.

	db 25	; Volume: 6.

	db 25	; Volume: 6.

	db 21	; Volume: 5.

	db 21	; Volume: 5.

	db 17	; Volume: 4.

	db 17	; Volume: 4.

	db 13	; Volume: 3.

	db 13	; Volume: 3.

	db 9	; Volume: 2.

	db 9	; Volume: 2.

	db 5	; Volume: 1.

	db 5	; Volume: 1.

	db 0	; Volume: 0.

ALIENALL_Instrument1Loop	db 0	; Volume: 0.

	db 4	; End the instrument.
ALIENALL_DisarkPointerRegionStart5
	dw ALIENALL_Instrument1Loop	; Loops.
ALIENALL_DisarkPointerRegionEnd5

ALIENALL_Instrument2
	db 0	; Speed.

	db 53	; Volume: 13.

	db 53	; Volume: 13.

	db 53	; Volume: 13.

	db 53	; Volume: 13.

	db 57	; Volume: 14.

	db 57	; Volume: 14.

	db 57	; Volume: 14.

	db 57	; Volume: 14.

	db 61	; Volume: 15.

	db 61	; Volume: 15.

	db 61	; Volume: 15.

	db 61	; Volume: 15.

	db 61	; Volume: 15.

	db 61	; Volume: 15.

	db 61	; Volume: 15.

	db 57	; Volume: 14.

	db 57	; Volume: 14.

	db 57	; Volume: 14.

	db 57	; Volume: 14.

	db 57	; Volume: 14.

	db 53	; Volume: 13.

	db 53	; Volume: 13.

	db 53	; Volume: 13.

	db 53	; Volume: 13.

	db 53	; Volume: 13.

	db 49	; Volume: 12.

	db 49	; Volume: 12.

	db 49	; Volume: 12.

	db 49	; Volume: 12.

	db 49	; Volume: 12.

	db 49	; Volume: 12.

	db 49	; Volume: 12.

ALIENALL_Instrument2Loop	db 49	; Volume: 12.

	db 49	; Volume: 12.

	db 49	; Volume: 12.

	db 49	; Volume: 12.

	db 49	; Volume: 12.

	db 49	; Volume: 12.

	db 4	; End the instrument.
ALIENALL_DisarkPointerRegionStart6
	dw ALIENALL_Instrument2Loop	; Loops.
ALIENALL_DisarkPointerRegionEnd6

ALIENALL_Instrument3
	db 0	; Speed.

	db 45	; Volume: 11.

	db 49	; Volume: 12.

	db 49	; Volume: 12.

	db 49	; Volume: 12.

	db 109	; Volume: 11.
	dw 1	; Pitch: 1.

	db 109	; Volume: 11.
	dw 1	; Pitch: 1.

	db 109	; Volume: 11.
	dw 1	; Pitch: 1.

	db 109	; Volume: 11.
	dw 1	; Pitch: 1.

	db 45	; Volume: 11.

	db 45	; Volume: 11.

	db 45	; Volume: 11.

	db 45	; Volume: 11.

	db 109	; Volume: 11.
	dw 1	; Pitch: 1.

	db 109	; Volume: 11.
	dw 1	; Pitch: 1.

	db 109	; Volume: 11.
	dw 1	; Pitch: 1.

	db 109	; Volume: 11.
	dw 1	; Pitch: 1.

	db 45	; Volume: 11.

	db 45	; Volume: 11.

	db 45	; Volume: 11.

	db 45	; Volume: 11.

	db 109	; Volume: 11.
	dw 1	; Pitch: 1.

	db 109	; Volume: 11.
	dw 1	; Pitch: 1.

	db 109	; Volume: 11.
	dw 1	; Pitch: 1.

	db 109	; Volume: 11.
	dw 1	; Pitch: 1.

	db 45	; Volume: 11.

	db 45	; Volume: 11.

	db 45	; Volume: 11.

	db 45	; Volume: 11.

	db 109	; Volume: 11.
	dw 1	; Pitch: 1.

	db 109	; Volume: 11.
	dw 1	; Pitch: 1.

	db 109	; Volume: 11.
	dw 1	; Pitch: 1.

	db 109	; Volume: 11.
	dw 1	; Pitch: 1.

ALIENALL_Instrument3Loop	db 45	; Volume: 11.

	db 45	; Volume: 11.

	db 45	; Volume: 11.

	db 45	; Volume: 11.

	db 109	; Volume: 11.
	dw -1	; Pitch: -1.

	db 109	; Volume: 11.
	dw -1	; Pitch: -1.

	db 109	; Volume: 11.
	dw -1	; Pitch: -1.

	db 109	; Volume: 11.
	dw -1	; Pitch: -1.

	db 4	; End the instrument.
ALIENALL_DisarkPointerRegionStart7
	dw ALIENALL_Instrument3Loop	; Loops.
ALIENALL_DisarkPointerRegionEnd7

ALIENALL_Instrument4
	db 0	; Speed.

	db 61	; Volume: 15.

	db 125	; Volume: 15.
	dw 1	; Pitch: 1.

	db 121	; Volume: 14.
	dw 2	; Pitch: 2.

	db 121	; Volume: 14.
	dw 3	; Pitch: 3.

	db 117	; Volume: 13.
	dw 2	; Pitch: 2.

	db 117	; Volume: 13.
	dw 1	; Pitch: 1.

	db 117	; Volume: 13.
	dw -1	; Pitch: -1.

	db 117	; Volume: 13.
	dw -2	; Pitch: -2.

	db 117	; Volume: 13.
	dw -3	; Pitch: -3.

	db 113	; Volume: 12.
	dw -2	; Pitch: -2.

	db 113	; Volume: 12.
	dw -1	; Pitch: -1.

	db 113	; Volume: 12.
	dw 1	; Pitch: 1.

	db 113	; Volume: 12.
	dw 3	; Pitch: 3.

	db 113	; Volume: 12.
	dw 5	; Pitch: 5.

	db 117	; Volume: 13.
	dw 3	; Pitch: 3.

	db 117	; Volume: 13.
	dw 1	; Pitch: 1.

	db 117	; Volume: 13.
	dw -1	; Pitch: -1.

	db 117	; Volume: 13.
	dw -3	; Pitch: -3.

	db 117	; Volume: 13.
	dw -5	; Pitch: -5.

	db 113	; Volume: 12.
	dw -3	; Pitch: -3.

	db 113	; Volume: 12.
	dw -1	; Pitch: -1.

	db 113	; Volume: 12.
	dw 1	; Pitch: 1.

	db 113	; Volume: 12.
	dw 4	; Pitch: 4.

	db 113	; Volume: 12.
	dw 7	; Pitch: 7.

	db 117	; Volume: 13.
	dw 4	; Pitch: 4.

	db 117	; Volume: 13.
	dw 1	; Pitch: 1.

	db 117	; Volume: 13.
	dw -1	; Pitch: -1.

	db 117	; Volume: 13.
	dw -4	; Pitch: -4.

	db 117	; Volume: 13.
	dw -7	; Pitch: -7.

	db 113	; Volume: 12.
	dw -4	; Pitch: -4.

	db 113	; Volume: 12.
	dw -1	; Pitch: -1.

ALIENALL_Instrument4Loop	db 49	; Volume: 12.

	db 4	; End the instrument.
ALIENALL_DisarkPointerRegionStart8
	dw ALIENALL_Instrument4Loop	; Loops.
ALIENALL_DisarkPointerRegionEnd8

ALIENALL_Instrument5
	db 0	; Speed.

	db 57	; Volume: 14.

	db 57	; Volume: 14.

	db 57	; Volume: 14.

	db 57	; Volume: 14.

	db 53	; Volume: 13.

	db 53	; Volume: 13.

	db 53	; Volume: 13.

	db 53	; Volume: 13.

	db 113	; Volume: 12.
	dw -1	; Pitch: -1.

	db 113	; Volume: 12.
	dw -2	; Pitch: -2.

	db 113	; Volume: 12.
	dw -1	; Pitch: -1.

	db 45	; Volume: 11.

	db 109	; Volume: 11.
	dw 1	; Pitch: 1.

	db 109	; Volume: 11.
	dw 2	; Pitch: 2.

	db 109	; Volume: 11.
	dw 1	; Pitch: 1.

	db 45	; Volume: 11.

	db 45	; Volume: 11.

	db 113	; Volume: 12.
	dw 1	; Pitch: 1.

	db 113	; Volume: 12.
	dw 2	; Pitch: 2.

	db 113	; Volume: 12.
	dw 3	; Pitch: 3.

	db 113	; Volume: 12.
	dw 2	; Pitch: 2.

	db 113	; Volume: 12.
	dw 1	; Pitch: 1.

	db 113	; Volume: 12.
	dw -1	; Pitch: -1.

	db 117	; Volume: 13.
	dw -2	; Pitch: -2.

	db 117	; Volume: 13.
	dw -3	; Pitch: -3.

	db 117	; Volume: 13.
	dw -2	; Pitch: -2.

	db 117	; Volume: 13.
	dw -1	; Pitch: -1.

	db 117	; Volume: 13.
	dw 2	; Pitch: 2.

	db 117	; Volume: 13.
	dw 3	; Pitch: 3.

	db 121	; Volume: 14.
	dw 4	; Pitch: 4.

	db 121	; Volume: 14.
	dw 3	; Pitch: 3.

	db 121	; Volume: 14.
	dw 2	; Pitch: 2.

ALIENALL_Instrument5Loop	db 113	; Volume: 12.
	dw 1	; Pitch: 1.

	db 117	; Volume: 13.
	dw 2	; Pitch: 2.

	db 117	; Volume: 13.
	dw 3	; Pitch: 3.

	db 117	; Volume: 13.
	dw 2	; Pitch: 2.

	db 117	; Volume: 13.
	dw 1	; Pitch: 1.

	db 117	; Volume: 13.
	dw -2	; Pitch: -2.

	db 117	; Volume: 13.
	dw -3	; Pitch: -3.

	db 121	; Volume: 14.
	dw -4	; Pitch: -4.

	db 121	; Volume: 14.
	dw -3	; Pitch: -3.

	db 121	; Volume: 14.
	dw -2	; Pitch: -2.

	db 4	; End the instrument.
ALIENALL_DisarkPointerRegionStart9
	dw ALIENALL_Instrument5Loop	; Loops.
ALIENALL_DisarkPointerRegionEnd9

ALIENALL_Instrument6
	db 0	; Speed.

	db 61	; Volume: 15.

	db 53	; Volume: 13.

	db 45	; Volume: 11.

	db 41	; Volume: 10.

	db 37	; Volume: 9.

	db 33	; Volume: 8.

	db 33	; Volume: 8.

	db 29	; Volume: 7.

	db 29	; Volume: 7.

	db 25	; Volume: 6.

	db 25	; Volume: 6.

	db 21	; Volume: 5.

	db 21	; Volume: 5.

	db 21	; Volume: 5.

	db 17	; Volume: 4.

	db 17	; Volume: 4.

	db 17	; Volume: 4.

	db 13	; Volume: 3.

	db 13	; Volume: 3.

	db 13	; Volume: 3.

	db 9	; Volume: 2.

	db 9	; Volume: 2.

	db 9	; Volume: 2.

	db 9	; Volume: 2.

	db 5	; Volume: 1.

	db 5	; Volume: 1.

	db 5	; Volume: 1.

	db 5	; Volume: 1.

	db 0	; Volume: 0.

	db 0	; Volume: 0.

	db 0	; Volume: 0.

ALIENALL_Instrument6Loop	db 0	; Volume: 0.

	db 4	; End the instrument.
ALIENALL_DisarkPointerRegionStart10
	dw ALIENALL_Instrument6Loop	; Loops.
ALIENALL_DisarkPointerRegionEnd10

ALIENALL_Instrument7
	db 0	; Speed.

	db 189	; Volume: 15.
	db 1	; Arpeggio: 0.
	db 12	; Noise: 12.

	db 125	; Volume: 15.
	dw 50	; Pitch: 50.

	db 125	; Volume: 15.
	dw 100	; Pitch: 100.

	db 125	; Volume: 15.
	dw 145	; Pitch: 145.

	db 125	; Volume: 15.
	dw 190	; Pitch: 190.

	db 121	; Volume: 14.
	dw 235	; Pitch: 235.

	db 121	; Volume: 14.
	dw 290	; Pitch: 290.

	db 117	; Volume: 13.
	dw 330	; Pitch: 330.

	db 113	; Volume: 12.
	dw 380	; Pitch: 380.

	db 105	; Volume: 10.
	dw 425	; Pitch: 425.

	db 89	; Volume: 6.
	dw 470	; Pitch: 470.

	db 0	; Volume: 0.

	db 0	; Volume: 0.

	db 0	; Volume: 0.

	db 0	; Volume: 0.

	db 0	; Volume: 0.

	db 0	; Volume: 0.

	db 0	; Volume: 0.

	db 0	; Volume: 0.

	db 0	; Volume: 0.

	db 0	; Volume: 0.

	db 0	; Volume: 0.

	db 0	; Volume: 0.

	db 0	; Volume: 0.

	db 0	; Volume: 0.

	db 0	; Volume: 0.

	db 0	; Volume: 0.

	db 0	; Volume: 0.

	db 0	; Volume: 0.

	db 0	; Volume: 0.

	db 0	; Volume: 0.

ALIENALL_Instrument7Loop	db 0	; Volume: 0.

	db 4	; End the instrument.
ALIENALL_DisarkPointerRegionStart11
	dw ALIENALL_Instrument7Loop	; Loops.
ALIENALL_DisarkPointerRegionEnd11

ALIENALL_Instrument8
	db 0	; Speed.

	db 185	; Volume: 14.
	db 1	; Arpeggio: 0.
	db 9	; Noise: 9.

	db 249	; Volume: 14.
	db 1	; Arpeggio: 0.
	db 9	; Noise: 9.
	dw 32	; Pitch: 32.

	db 245	; Volume: 13.
	db 1	; Arpeggio: 0.
	db 8	; Noise: 8.
	dw 64	; Pitch: 64.

	db 245	; Volume: 13.
	db 1	; Arpeggio: 0.
	db 6	; Noise: 6.
	dw 96	; Pitch: 96.

	db 241	; Volume: 12.
	db 1	; Arpeggio: 0.
	db 6	; Noise: 6.
	dw 160	; Pitch: 160.

	db 241	; Volume: 12.
	db 1	; Arpeggio: 0.
	db 7	; Noise: 7.
	dw 224	; Pitch: 224.

	db 173	; Volume: 11.
	db 1	; Arpeggio: 0.
	db 8	; Noise: 8.

	db 237	; Volume: 11.
	db 1	; Arpeggio: 0.
	db 9	; Noise: 9.
	dw 32	; Pitch: 32.

	db 233	; Volume: 10.
	db 1	; Arpeggio: 0.
	db 11	; Noise: 11.
	dw 64	; Pitch: 64.

	db 233	; Volume: 10.
	db 1	; Arpeggio: 0.
	db 10	; Noise: 10.
	dw 96	; Pitch: 96.

	db 229	; Volume: 9.
	db 1	; Arpeggio: 0.
	db 9	; Noise: 9.
	dw 160	; Pitch: 160.

	db 229	; Volume: 9.
	db 1	; Arpeggio: 0.
	db 6	; Noise: 6.
	dw 224	; Pitch: 224.

	db 161	; Volume: 8.
	db 1	; Arpeggio: 0.
	db 6	; Noise: 6.

	db 225	; Volume: 8.
	db 1	; Arpeggio: 0.
	db 8	; Noise: 8.
	dw 32	; Pitch: 32.

	db 217	; Volume: 6.
	db 1	; Arpeggio: 0.
	db 8	; Noise: 8.
	dw 64	; Pitch: 64.

	db 213	; Volume: 5.
	db 1	; Arpeggio: 0.
	db 7	; Noise: 7.
	dw 96	; Pitch: 96.

	db 201	; Volume: 2.
	db 1	; Arpeggio: 0.
	db 6	; Noise: 6.
	dw 128	; Pitch: 128.

	db 0	; Volume: 0.

	db 0	; Volume: 0.

	db 0	; Volume: 0.

	db 0	; Volume: 0.

	db 0	; Volume: 0.

	db 0	; Volume: 0.

	db 0	; Volume: 0.

	db 0	; Volume: 0.

	db 0	; Volume: 0.

	db 0	; Volume: 0.

	db 0	; Volume: 0.

	db 0	; Volume: 0.

	db 0	; Volume: 0.

	db 0	; Volume: 0.

ALIENALL_Instrument8Loop	db 0	; Volume: 0.

	db 4	; End the instrument.
ALIENALL_DisarkPointerRegionStart12
	dw ALIENALL_Instrument8Loop	; Loops.
ALIENALL_DisarkPointerRegionEnd12

ALIENALL_Instrument9
	db 0	; Speed.

ALIENALL_Instrument9Loop	db 82
	db 4	; End the instrument.
ALIENALL_DisarkPointerRegionStart13
	dw ALIENALL_Instrument9Loop	; Loops.
ALIENALL_DisarkPointerRegionEnd13

ALIENALL_DisarkByteRegionEnd3
ALIENALL_ArpeggioIndexes
ALIENALL_DisarkPointerRegionStart14
	dw ALIENALL_Arpeggio1
	dw ALIENALL_Arpeggio2
	dw ALIENALL_Arpeggio3
	dw ALIENALL_Arpeggio4
ALIENALL_DisarkPointerRegionEnd14

ALIENALL_DisarkByteRegionStart15
ALIENALL_Arpeggio1
	db 0	; Speed

	db 0	; Value: 0
	db 0	; Value: 0
	db -10	; Value: -5
	db -10	; Value: -5
	db -16	; Value: -8
	db -16	; Value: -8
	db 0	; Value: 0
	db 0	; Value: 0
	db -10	; Value: -5
	db -10	; Value: -5
	db -16	; Value: -8
	db -16	; Value: -8
	db 0	; Value: 0
	db 0	; Value: 0
	db -10	; Value: -5
	db -10	; Value: -5
	db -16	; Value: -8
	db -16	; Value: -8
	db 0	; Value: 0
	db 0	; Value: 0
	db -10	; Value: -5
	db -10	; Value: -5
	db -16	; Value: -8
	db -16	; Value: -8
	db 0	; Value: 0
	db 0	; Value: 0
	db -10	; Value: -5
	db -10	; Value: -5
	db -16	; Value: -8
	db -16	; Value: -8
	db 0	; Value: 0
	db 0	; Value: 0
	db 0 * 2 + 1	; Loops to index 0.
ALIENALL_Arpeggio2
	db 0	; Speed

	db 0	; Value: 0
	db 0	; Value: 0
	db -8	; Value: -4
	db -8	; Value: -4
	db -14	; Value: -7
	db -14	; Value: -7
	db 0	; Value: 0
	db 0	; Value: 0
	db -8	; Value: -4
	db -8	; Value: -4
	db -14	; Value: -7
	db -14	; Value: -7
	db 0	; Value: 0
	db 0	; Value: 0
	db -8	; Value: -4
	db -8	; Value: -4
	db -14	; Value: -7
	db -14	; Value: -7
	db 0	; Value: 0
	db 0	; Value: 0
	db -8	; Value: -4
	db -8	; Value: -4
	db -14	; Value: -7
	db -14	; Value: -7
	db 0	; Value: 0
	db 0	; Value: 0
	db -8	; Value: -4
	db -8	; Value: -4
	db -14	; Value: -7
	db -14	; Value: -7
	db 0	; Value: 0
	db 0	; Value: 0
	db 0 * 2 + 1	; Loops to index 0.
ALIENALL_Arpeggio3
	db 0	; Speed

	db 0	; Value: 0
	db 0	; Value: 0
	db -8	; Value: -4
	db -8	; Value: -4
	db -18	; Value: -9
	db -18	; Value: -9
	db 0	; Value: 0
	db 0	; Value: 0
	db -8	; Value: -4
	db -8	; Value: -4
	db -18	; Value: -9
	db -18	; Value: -9
	db 0	; Value: 0
	db 0	; Value: 0
	db -8	; Value: -4
	db -8	; Value: -4
	db -18	; Value: -9
	db -18	; Value: -9
	db 0	; Value: 0
	db 0	; Value: 0
	db -8	; Value: -4
	db -8	; Value: -4
	db -18	; Value: -9
	db -18	; Value: -9
	db 0	; Value: 0
	db 0	; Value: 0
	db -8	; Value: -4
	db -8	; Value: -4
	db -18	; Value: -9
	db -18	; Value: -9
	db 0	; Value: 0
	db 0	; Value: 0
	db 0 * 2 + 1	; Loops to index 0.
ALIENALL_Arpeggio4
	db 0	; Speed

	db 0	; Value: 0
	db 0	; Value: 0
	db -6	; Value: -3
	db -6	; Value: -3
	db -14	; Value: -7
	db -14	; Value: -7
	db 0	; Value: 0
	db 0	; Value: 0
	db -6	; Value: -3
	db -6	; Value: -3
	db -14	; Value: -7
	db -14	; Value: -7
	db 0	; Value: 0
	db 0	; Value: 0
	db -6	; Value: -3
	db -6	; Value: -3
	db -14	; Value: -7
	db -14	; Value: -7
	db 0	; Value: 0
	db 0	; Value: 0
	db -6	; Value: -3
	db -6	; Value: -3
	db -14	; Value: -7
	db -14	; Value: -7
	db 0	; Value: 0
	db 0	; Value: 0
	db -6	; Value: -3
	db -6	; Value: -3
	db -14	; Value: -7
	db -14	; Value: -7
	db 0	; Value: 0
	db 0	; Value: 0
	db 0 * 2 + 1	; Loops to index 0.
ALIENALL_DisarkByteRegionEnd15

ALIENALL_PitchIndexes
ALIENALL_DisarkPointerRegionStart16
ALIENALL_DisarkPointerRegionEnd16

ALIENALL_DisarkByteRegionStart17
ALIENALL_DisarkByteRegionEnd17

; ALIENALL, Subsong 0.
; ----------------------------------

ALIENALL_Subsong0
ALIENALL_Subsong0DisarkPointerRegionStart0
	dw ALIENALL_Subsong0_NoteIndexes	; Index table for the notes.
	dw ALIENALL_Subsong0_TrackIndexes	; Index table for the Tracks.
ALIENALL_Subsong0DisarkPointerRegionEnd0

ALIENALL_Subsong0DisarkByteRegionStart1
	db 6	; Initial speed.

	db 1	; Most used instrument.
	db 7	; Second most used instrument.

	db 0	; Most used wait.
	db 1	; Second most used wait.

	db 33	; Default start note in tracks.
	db 2	; Default start instrument in tracks.
	db 0	; Default start wait in tracks.

	db 12	; Are there effects? 12 if yes, 13 if not. Don't ask.
ALIENALL_Subsong0DisarkByteRegionEnd1

; The Linker.
ALIENALL_Subsong0DisarkByteRegionStart2
; Pattern 0
	db 170	; State byte.
	db 31	; New height.
	db 134	; New track (0) for channel 1, as a reference (index 6).
	db 135	; New track (1) for channel 2, as a reference (index 7).
	db 135	; New track (1) for channel 3, as a reference (index 7).

; Pattern 1
	db 128	; State byte.
	db ((ALIENALL_Subsong0_Track2 - ($ + 2)) & #ff00) / 256	; New track (2) for channel 3, as an offset. Offset MSB, then LSB.
	db ((ALIENALL_Subsong0_Track2 - ($ + 1)) & 255)

; Pattern 2
	db 32	; State byte.
	db ((ALIENALL_Subsong0_Track3 - ($ + 2)) & #ff00) / 256	; New track (3) for channel 2, as an offset. Offset MSB, then LSB.
	db ((ALIENALL_Subsong0_Track3 - ($ + 1)) & 255)

; Pattern 3
	db 136	; State byte.
	db ((ALIENALL_Subsong0_Track4 - ($ + 2)) & #ff00) / 256	; New track (4) for channel 1, as an offset. Offset MSB, then LSB.
	db ((ALIENALL_Subsong0_Track4 - ($ + 1)) & 255)
	db ((ALIENALL_Subsong0_Track5 - ($ + 2)) & #ff00) / 256	; New track (5) for channel 3, as an offset. Offset MSB, then LSB.
	db ((ALIENALL_Subsong0_Track5 - ($ + 1)) & 255)

; Pattern 4
	db 168	; State byte.
	db 134	; New track (0) for channel 1, as a reference (index 6).
	db ((ALIENALL_Subsong0_Track6 - ($ + 2)) & #ff00) / 256	; New track (6) for channel 2, as an offset. Offset MSB, then LSB.
	db ((ALIENALL_Subsong0_Track6 - ($ + 1)) & 255)
	db 128	; New track (7) for channel 3, as a reference (index 0).

; Pattern 5
	db 168	; State byte.
	db ((ALIENALL_Subsong0_Track4 - ($ + 2)) & #ff00) / 256	; New track (4) for channel 1, as an offset. Offset MSB, then LSB.
	db ((ALIENALL_Subsong0_Track4 - ($ + 1)) & 255)
	db ((ALIENALL_Subsong0_Track8 - ($ + 2)) & #ff00) / 256	; New track (8) for channel 2, as an offset. Offset MSB, then LSB.
	db ((ALIENALL_Subsong0_Track8 - ($ + 1)) & 255)
	db 129	; New track (9) for channel 3, as a reference (index 1).

; Pattern 6
ALIENALL_Subsong0_Loop
	db 168	; State byte.
	db 130	; New track (10) for channel 1, as a reference (index 2).
	db 136	; New track (11) for channel 2, as a reference (index 8).
	db 128	; New track (7) for channel 3, as a reference (index 0).

; Pattern 7
	db 168	; State byte.
	db 131	; New track (12) for channel 1, as a reference (index 3).
	db ((ALIENALL_Subsong0_Track13 - ($ + 2)) & #ff00) / 256	; New track (13) for channel 2, as an offset. Offset MSB, then LSB.
	db ((ALIENALL_Subsong0_Track13 - ($ + 1)) & 255)
	db 129	; New track (9) for channel 3, as a reference (index 1).

; Pattern 8
	db 168	; State byte.
	db 130	; New track (10) for channel 1, as a reference (index 2).
	db 136	; New track (11) for channel 2, as a reference (index 8).
	db 128	; New track (7) for channel 3, as a reference (index 0).

; Pattern 9
	db 168	; State byte.
	db 131	; New track (12) for channel 1, as a reference (index 3).
	db ((ALIENALL_Subsong0_Track14 - ($ + 2)) & #ff00) / 256	; New track (14) for channel 2, as an offset. Offset MSB, then LSB.
	db ((ALIENALL_Subsong0_Track14 - ($ + 1)) & 255)
	db 129	; New track (9) for channel 3, as a reference (index 1).

; Pattern 10
	db 168	; State byte.
	db 130	; New track (10) for channel 1, as a reference (index 2).
	db ((ALIENALL_Subsong0_Track15 - ($ + 2)) & #ff00) / 256	; New track (15) for channel 2, as an offset. Offset MSB, then LSB.
	db ((ALIENALL_Subsong0_Track15 - ($ + 1)) & 255)
	db 128	; New track (7) for channel 3, as a reference (index 0).

; Pattern 11
	db 168	; State byte.
	db 131	; New track (12) for channel 1, as a reference (index 3).
	db ((ALIENALL_Subsong0_Track16 - ($ + 2)) & #ff00) / 256	; New track (16) for channel 2, as an offset. Offset MSB, then LSB.
	db ((ALIENALL_Subsong0_Track16 - ($ + 1)) & 255)
	db 129	; New track (9) for channel 3, as a reference (index 1).

; Pattern 12
	db 168	; State byte.
	db 130	; New track (10) for channel 1, as a reference (index 2).
	db ((ALIENALL_Subsong0_Track15 - ($ + 2)) & #ff00) / 256	; New track (15) for channel 2, as an offset. Offset MSB, then LSB.
	db ((ALIENALL_Subsong0_Track15 - ($ + 1)) & 255)
	db 128	; New track (7) for channel 3, as a reference (index 0).

; Pattern 13
	db 168	; State byte.
	db 131	; New track (12) for channel 1, as a reference (index 3).
	db ((ALIENALL_Subsong0_Track17 - ($ + 2)) & #ff00) / 256	; New track (17) for channel 2, as an offset. Offset MSB, then LSB.
	db ((ALIENALL_Subsong0_Track17 - ($ + 1)) & 255)
	db ((ALIENALL_Subsong0_Track18 - ($ + 2)) & #ff00) / 256	; New track (18) for channel 3, as an offset. Offset MSB, then LSB.
	db ((ALIENALL_Subsong0_Track18 - ($ + 1)) & 255)

; Pattern 14
	db 168	; State byte.
	db 132	; New track (19) for channel 1, as a reference (index 4).
	db 137	; New track (20) for channel 2, as a reference (index 9).
	db 128	; New track (7) for channel 3, as a reference (index 0).

; Pattern 15
	db 168	; State byte.
	db 133	; New track (21) for channel 1, as a reference (index 5).
	db 138	; New track (22) for channel 2, as a reference (index 10).
	db 129	; New track (9) for channel 3, as a reference (index 1).

; Pattern 16
	db 168	; State byte.
	db 132	; New track (19) for channel 1, as a reference (index 4).
	db 137	; New track (20) for channel 2, as a reference (index 9).
	db 128	; New track (7) for channel 3, as a reference (index 0).

; Pattern 17
	db 168	; State byte.
	db 133	; New track (21) for channel 1, as a reference (index 5).
	db 138	; New track (22) for channel 2, as a reference (index 10).
	db 129	; New track (9) for channel 3, as a reference (index 1).

; Pattern 18
	db 168	; State byte.
	db 130	; New track (10) for channel 1, as a reference (index 2).
	db 136	; New track (11) for channel 2, as a reference (index 8).
	db 128	; New track (7) for channel 3, as a reference (index 0).

; Pattern 19
	db 168	; State byte.
	db 131	; New track (12) for channel 1, as a reference (index 3).
	db ((ALIENALL_Subsong0_Track13 - ($ + 2)) & #ff00) / 256	; New track (13) for channel 2, as an offset. Offset MSB, then LSB.
	db ((ALIENALL_Subsong0_Track13 - ($ + 1)) & 255)
	db 129	; New track (9) for channel 3, as a reference (index 1).

; Pattern 20
	db 168	; State byte.
	db 130	; New track (10) for channel 1, as a reference (index 2).
	db 136	; New track (11) for channel 2, as a reference (index 8).
	db 128	; New track (7) for channel 3, as a reference (index 0).

; Pattern 21
	db 168	; State byte.
	db 131	; New track (12) for channel 1, as a reference (index 3).
	db ((ALIENALL_Subsong0_Track14 - ($ + 2)) & #ff00) / 256	; New track (14) for channel 2, as an offset. Offset MSB, then LSB.
	db ((ALIENALL_Subsong0_Track14 - ($ + 1)) & 255)
	db 129	; New track (9) for channel 3, as a reference (index 1).

; Pattern 22
	db 168	; State byte.
	db 132	; New track (19) for channel 1, as a reference (index 4).
	db ((ALIENALL_Subsong0_Track23 - ($ + 2)) & #ff00) / 256	; New track (23) for channel 2, as an offset. Offset MSB, then LSB.
	db ((ALIENALL_Subsong0_Track23 - ($ + 1)) & 255)
	db 128	; New track (7) for channel 3, as a reference (index 0).

; Pattern 23
	db 168	; State byte.
	db 133	; New track (21) for channel 1, as a reference (index 5).
	db ((ALIENALL_Subsong0_Track24 - ($ + 2)) & #ff00) / 256	; New track (24) for channel 2, as an offset. Offset MSB, then LSB.
	db ((ALIENALL_Subsong0_Track24 - ($ + 1)) & 255)
	db 129	; New track (9) for channel 3, as a reference (index 1).

; Pattern 24
	db 168	; State byte.
	db 132	; New track (19) for channel 1, as a reference (index 4).
	db ((ALIENALL_Subsong0_Track23 - ($ + 2)) & #ff00) / 256	; New track (23) for channel 2, as an offset. Offset MSB, then LSB.
	db ((ALIENALL_Subsong0_Track23 - ($ + 1)) & 255)
	db 128	; New track (7) for channel 3, as a reference (index 0).

; Pattern 25
	db 168	; State byte.
	db 133	; New track (21) for channel 1, as a reference (index 5).
	db ((ALIENALL_Subsong0_Track25 - ($ + 2)) & #ff00) / 256	; New track (25) for channel 2, as an offset. Offset MSB, then LSB.
	db ((ALIENALL_Subsong0_Track25 - ($ + 1)) & 255)
	db ((ALIENALL_Subsong0_Track26 - ($ + 2)) & #ff00) / 256	; New track (26) for channel 3, as an offset. Offset MSB, then LSB.
	db ((ALIENALL_Subsong0_Track26 - ($ + 1)) & 255)

; Pattern 26
	db 168	; State byte.
	db 132	; New track (19) for channel 1, as a reference (index 4).
	db 137	; New track (20) for channel 2, as a reference (index 9).
	db 128	; New track (7) for channel 3, as a reference (index 0).

; Pattern 27
	db 168	; State byte.
	db 133	; New track (21) for channel 1, as a reference (index 5).
	db 138	; New track (22) for channel 2, as a reference (index 10).
	db 129	; New track (9) for channel 3, as a reference (index 1).

; Pattern 28
	db 168	; State byte.
	db 132	; New track (19) for channel 1, as a reference (index 4).
	db 137	; New track (20) for channel 2, as a reference (index 9).
	db 128	; New track (7) for channel 3, as a reference (index 0).

; Pattern 29
	db 168	; State byte.
	db 133	; New track (21) for channel 1, as a reference (index 5).
	db 138	; New track (22) for channel 2, as a reference (index 10).
	db 129	; New track (9) for channel 3, as a reference (index 1).

; Pattern 30
	db 168	; State byte.
	db 134	; New track (0) for channel 1, as a reference (index 6).
	db 135	; New track (1) for channel 2, as a reference (index 7).
	db 135	; New track (1) for channel 3, as a reference (index 7).

	db 1	; End of the Song.
	db 0	; Speed to 0, meaning "end of song".
ALIENALL_Subsong0DisarkByteRegionEnd2
ALIENALL_Subsong0DisarkPointerRegionStart3
	dw ALIENALL_Subsong0_Loop

ALIENALL_Subsong0DisarkPointerRegionEnd3
; The indexes of the tracks.
ALIENALL_Subsong0_TrackIndexes
ALIENALL_Subsong0DisarkPointerRegionStart4
	dw ALIENALL_Subsong0_Track7	; Track 7, index 0.
	dw ALIENALL_Subsong0_Track9	; Track 9, index 1.
	dw ALIENALL_Subsong0_Track10	; Track 10, index 2.
	dw ALIENALL_Subsong0_Track12	; Track 12, index 3.
	dw ALIENALL_Subsong0_Track19	; Track 19, index 4.
	dw ALIENALL_Subsong0_Track21	; Track 21, index 5.
	dw ALIENALL_Subsong0_Track0	; Track 0, index 6.
	dw ALIENALL_Subsong0_Track1	; Track 1, index 7.
	dw ALIENALL_Subsong0_Track11	; Track 11, index 8.
	dw ALIENALL_Subsong0_Track20	; Track 20, index 9.
	dw ALIENALL_Subsong0_Track22	; Track 22, index 10.
ALIENALL_Subsong0DisarkPointerRegionEnd4

ALIENALL_Subsong0DisarkByteRegionStart5
ALIENALL_Subsong0_Track0
	db 12	; Note with effects flag.
	db 177	; New instrument (6). Note reference (1). Secondary wait (1).
	db 6	;   Escape instrument value.
	db 2	;    Volume effect, with inverted volume: 0.
	db 71	; Note reference (7). Primary wait (0).
	db 12	; Note with effects flag.
	db 65	; Note reference (1). Primary wait (0).
	db 50	;    Volume effect, with inverted volume: 3.
	db 12	; Note with effects flag.
	db 66	; Note reference (2). Primary wait (0).
	db 2	;    Volume effect, with inverted volume: 0.
	db 12	; Note with effects flag.
	db 71	; Note reference (7). Primary wait (0).
	db 50	;    Volume effect, with inverted volume: 3.
	db 12	; Note with effects flag.
	db 71	; Note reference (7). Primary wait (0).
	db 2	;    Volume effect, with inverted volume: 0.
	db 12	; Note with effects flag.
	db 66	; Note reference (2). Primary wait (0).
	db 50	;    Volume effect, with inverted volume: 3.
	db 12	; Note with effects flag.
	db 65	; Note reference (1). Primary wait (0).
	db 2	;    Volume effect, with inverted volume: 0.
	db 12	; Note with effects flag.
	db 71	; Note reference (7). Primary wait (0).
	db 50	;    Volume effect, with inverted volume: 3.
	db 12	; Note with effects flag.
	db 71	; Note reference (7). Primary wait (0).
	db 2	;    Volume effect, with inverted volume: 0.
	db 12	; Note with effects flag.
	db 65	; Note reference (1). Primary wait (0).
	db 50	;    Volume effect, with inverted volume: 3.
	db 12	; Note with effects flag.
	db 66	; Note reference (2). Primary wait (0).
	db 2	;    Volume effect, with inverted volume: 0.
	db 12	; Note with effects flag.
	db 71	; Note reference (7). Primary wait (0).
	db 50	;    Volume effect, with inverted volume: 3.
	db 12	; Note with effects flag.
	db 71	; Note reference (7). Primary wait (0).
	db 2	;    Volume effect, with inverted volume: 0.
	db 12	; Note with effects flag.
	db 66	; Note reference (2). Primary wait (0).
	db 50	;    Volume effect, with inverted volume: 3.
	db 12	; Note with effects flag.
	db 67	; Note reference (3). Primary wait (0).
	db 2	;    Volume effect, with inverted volume: 0.
	db 12	; Note with effects flag.
	db 71	; Note reference (7). Primary wait (0).
	db 50	;    Volume effect, with inverted volume: 3.
	db 12	; Note with effects flag.
	db 66	; Note reference (2). Primary wait (0).
	db 2	;    Volume effect, with inverted volume: 0.
	db 12	; Note with effects flag.
	db 67	; Note reference (3). Primary wait (0).
	db 50	;    Volume effect, with inverted volume: 3.
	db 12	; Note with effects flag.
	db 67	; Note reference (3). Primary wait (0).
	db 2	;    Volume effect, with inverted volume: 0.
	db 12	; Note with effects flag.
	db 66	; Note reference (2). Primary wait (0).
	db 50	;    Volume effect, with inverted volume: 3.
	db 12	; Note with effects flag.
	db 65	; Note reference (1). Primary wait (0).
	db 2	;    Volume effect, with inverted volume: 0.
	db 69	; Note reference (5). Primary wait (0).
	db 12	; Note with effects flag.
	db 66	; Note reference (2). Primary wait (0).
	db 82	;    Volume effect, with inverted volume: 5.
	db 12	; Note with effects flag.
	db 69	; Note reference (5). Primary wait (0).
	db 2	;    Volume effect, with inverted volume: 0.
	db 129	; Note reference (1). Secondary wait (1).
	db 67	; Note reference (3). Primary wait (0).
	db 12	; Note with effects flag.
	db 65	; Note reference (1). Primary wait (0).
	db 50	;    Volume effect, with inverted volume: 3.
	db 12	; Note with effects flag.
	db 69	; Note reference (5). Primary wait (0).
	db 2	;    Volume effect, with inverted volume: 0.
	db 12	; Note with effects flag.
	db 195	; Note reference (3). New wait (127).
	db 127	;   Escape wait value.
	db 50	;    Volume effect, with inverted volume: 3.

ALIENALL_Subsong0_Track1
	db 205	; New wait (127).
	db 127	;   Escape wait value.

ALIENALL_Subsong0_Track2
	db 12	; Note with effects flag.
	db 255	; New instrument (9). Same escaped note: 33. New wait (15).
	db 9	;   Escape instrument value.
	db 15	;   Escape wait value.
	db 0	;    Reset effect, with inverted volume: 0.
	db 196	; Note reference (4). New wait (127).
	db 127	;   Escape wait value.

ALIENALL_Subsong0_Track3
	db 224	; Secondary instrument (7). Note reference (0). New wait (3).
	db 3	;   Escape wait value.
	db 184	; New instrument (8). Note reference (8). Secondary wait (1).
	db 8	;   Escape instrument value.
	db 160	; Secondary instrument (7). Note reference (0). Secondary wait (1).
	db 160	; Secondary instrument (7). Note reference (0). Secondary wait (1).
	db 96	; Secondary instrument (7). Note reference (0). Primary wait (0).
	db 96	; Secondary instrument (7). Note reference (0). Primary wait (0).
	db 136	; Note reference (8). Secondary wait (1).
	db 160	; Secondary instrument (7). Note reference (0). Secondary wait (1).
	db 32	; Secondary instrument (7). Note reference (0). 
	db 136	; Note reference (8). Secondary wait (1).
	db 160	; Secondary instrument (7). Note reference (0). Secondary wait (1).
	db 160	; Secondary instrument (7). Note reference (0). Secondary wait (1).
	db 96	; Secondary instrument (7). Note reference (0). Primary wait (0).
	db 96	; Secondary instrument (7). Note reference (0). Primary wait (0).
	db 136	; Note reference (8). Secondary wait (1).
	db 224	; Secondary instrument (7). Note reference (0). New wait (127).
	db 127	;   Escape wait value.

ALIENALL_Subsong0_Track4
	db 12	; Note with effects flag.
	db 249	; New instrument (6). Note reference (9). New wait (2).
	db 6	;   Escape instrument value.
	db 2	;   Escape wait value.
	db 2	;    Volume effect, with inverted volume: 0.
	db 12	; Note with effects flag.
	db 9	; Note reference (9). 
	db 50	;    Volume effect, with inverted volume: 3.
	db 12	; Note with effects flag.
	db 137	; Note reference (9). Secondary wait (1).
	db 82	;    Volume effect, with inverted volume: 5.
	db 12	; Note with effects flag.
	db 138	; Note reference (10). Secondary wait (1).
	db 2	;    Volume effect, with inverted volume: 0.
	db 66	; Note reference (2). Primary wait (0).
	db 12	; Note with effects flag.
	db 74	; Note reference (10). Primary wait (0).
	db 50	;    Volume effect, with inverted volume: 3.
	db 12	; Note with effects flag.
	db 67	; Note reference (3). Primary wait (0).
	db 2	;    Volume effect, with inverted volume: 0.
	db 12	; Note with effects flag.
	db 66	; Note reference (2). Primary wait (0).
	db 50	;    Volume effect, with inverted volume: 3.
	db 12	; Note with effects flag.
	db 65	; Note reference (1). Primary wait (0).
	db 2	;    Volume effect, with inverted volume: 0.
	db 67	; Note reference (3). Primary wait (0).
	db 12	; Note with effects flag.
	db 66	; Note reference (2). Primary wait (0).
	db 82	;    Volume effect, with inverted volume: 5.
	db 12	; Note with effects flag.
	db 65	; Note reference (1). Primary wait (0).
	db 50	;    Volume effect, with inverted volume: 3.
	db 131	; Note reference (3). Secondary wait (1).
	db 12	; Note with effects flag.
	db 65	; Note reference (1). Primary wait (0).
	db 82	;    Volume effect, with inverted volume: 5.
	db 195	; Note reference (3). New wait (127).
	db 127	;   Escape wait value.

ALIENALL_Subsong0_Track5
	db 12	; Note with effects flag.
	db 246	; New instrument (9). Note reference (6). New wait (15).
	db 9	;   Escape instrument value.
	db 15	;   Escape wait value.
	db 0	;    Reset effect, with inverted volume: 0.
	db 196	; Note reference (4). New wait (127).
	db 127	;   Escape wait value.

ALIENALL_Subsong0_Track6
	db 242	; New instrument (3). Note reference (2). New wait (9).
	db 3	;   Escape instrument value.
	db 9	;   Escape wait value.
	db 138	; Note reference (10). Secondary wait (1).
	db 139	; Note reference (11). Secondary wait (1).
	db 130	; Note reference (2). Secondary wait (1).
	db 195	; Note reference (3). New wait (7).
	db 7	;   Escape wait value.
	db 129	; Note reference (1). Secondary wait (1).
	db 195	; Note reference (3). New wait (127).
	db 127	;   Escape wait value.

ALIENALL_Subsong0_Track7
	db 12	; Note with effects flag.
	db 96	; Secondary instrument (7). Note reference (0). Primary wait (0).
	db 0	;    Reset effect, with inverted volume: 0.
	db 255	; New instrument (9). Same escaped note: 33. New wait (2).
	db 9	;   Escape instrument value.
	db 2	;   Escape wait value.
	db 120	; New instrument (8). Note reference (8). Primary wait (0).
	db 8	;   Escape instrument value.
	db 127	; New instrument (9). Same escaped note: 33. Primary wait (0).
	db 9	;   Escape instrument value.
	db 96	; Secondary instrument (7). Note reference (0). Primary wait (0).
	db 79	; Same escaped note: 33. Primary wait (0).
	db 96	; Secondary instrument (7). Note reference (0). Primary wait (0).
	db 79	; Same escaped note: 33. Primary wait (0).
	db 96	; Secondary instrument (7). Note reference (0). Primary wait (0).
	db 96	; Secondary instrument (7). Note reference (0). Primary wait (0).
	db 120	; New instrument (8). Note reference (8). Primary wait (0).
	db 8	;   Escape instrument value.
	db 127	; New instrument (9). Same escaped note: 33. Primary wait (0).
	db 9	;   Escape instrument value.
	db 96	; Secondary instrument (7). Note reference (0). Primary wait (0).
	db 79	; Same escaped note: 33. Primary wait (0).
	db 96	; Secondary instrument (7). Note reference (0). Primary wait (0).
	db 4	; Note reference (4). 
	db 120	; New instrument (8). Note reference (8). Primary wait (0).
	db 8	;   Escape instrument value.
	db 116	; New instrument (9). Note reference (4). Primary wait (0).
	db 9	;   Escape instrument value.
	db 96	; Secondary instrument (7). Note reference (0). Primary wait (0).
	db 68	; Note reference (4). Primary wait (0).
	db 96	; Secondary instrument (7). Note reference (0). Primary wait (0).
	db 68	; Note reference (4). Primary wait (0).
	db 96	; Secondary instrument (7). Note reference (0). Primary wait (0).
	db 96	; Secondary instrument (7). Note reference (0). Primary wait (0).
	db 120	; New instrument (8). Note reference (8). Primary wait (0).
	db 8	;   Escape instrument value.
	db 116	; New instrument (9). Note reference (4). Primary wait (0).
	db 9	;   Escape instrument value.
	db 96	; Secondary instrument (7). Note reference (0). Primary wait (0).
	db 196	; Note reference (4). New wait (127).
	db 127	;   Escape wait value.

ALIENALL_Subsong0_Track8
	db 249	; New instrument (3). Note reference (9). New wait (7).
	db 3	;   Escape instrument value.
	db 7	;   Escape wait value.
	db 138	; Note reference (10). Secondary wait (1).
	db 130	; Note reference (2). Secondary wait (1).
	db 131	; Note reference (3). Secondary wait (1).
	db 129	; Note reference (1). Secondary wait (1).
	db 197	; Note reference (5). New wait (5).
	db 5	;   Escape wait value.
	db 1	; Note reference (1). 
	db 195	; Note reference (3). New wait (127).
	db 127	;   Escape wait value.

ALIENALL_Subsong0_Track9
	db 12	; Note with effects flag.
	db 96	; Secondary instrument (7). Note reference (0). Primary wait (0).
	db 0	;    Reset effect, with inverted volume: 0.
	db 246	; New instrument (9). Note reference (6). New wait (2).
	db 9	;   Escape instrument value.
	db 2	;   Escape wait value.
	db 120	; New instrument (8). Note reference (8). Primary wait (0).
	db 8	;   Escape instrument value.
	db 118	; New instrument (9). Note reference (6). Primary wait (0).
	db 9	;   Escape instrument value.
	db 96	; Secondary instrument (7). Note reference (0). Primary wait (0).
	db 70	; Note reference (6). Primary wait (0).
	db 96	; Secondary instrument (7). Note reference (0). Primary wait (0).
	db 70	; Note reference (6). Primary wait (0).
	db 96	; Secondary instrument (7). Note reference (0). Primary wait (0).
	db 96	; Secondary instrument (7). Note reference (0). Primary wait (0).
	db 120	; New instrument (8). Note reference (8). Primary wait (0).
	db 8	;   Escape instrument value.
	db 118	; New instrument (9). Note reference (6). Primary wait (0).
	db 9	;   Escape instrument value.
	db 96	; Secondary instrument (7). Note reference (0). Primary wait (0).
	db 70	; Note reference (6). Primary wait (0).
	db 96	; Secondary instrument (7). Note reference (0). Primary wait (0).
	db 4	; Note reference (4). 
	db 120	; New instrument (8). Note reference (8). Primary wait (0).
	db 8	;   Escape instrument value.
	db 116	; New instrument (9). Note reference (4). Primary wait (0).
	db 9	;   Escape instrument value.
	db 96	; Secondary instrument (7). Note reference (0). Primary wait (0).
	db 68	; Note reference (4). Primary wait (0).
	db 96	; Secondary instrument (7). Note reference (0). Primary wait (0).
	db 68	; Note reference (4). Primary wait (0).
	db 96	; Secondary instrument (7). Note reference (0). Primary wait (0).
	db 96	; Secondary instrument (7). Note reference (0). Primary wait (0).
	db 120	; New instrument (8). Note reference (8). Primary wait (0).
	db 8	;   Escape instrument value.
	db 116	; New instrument (9). Note reference (4). Primary wait (0).
	db 9	;   Escape instrument value.
	db 96	; Secondary instrument (7). Note reference (0). Primary wait (0).
	db 196	; Note reference (4). New wait (127).
	db 127	;   Escape wait value.

ALIENALL_Subsong0_Track10
	db 12	; Note with effects flag.
	db 193	; Note reference (1). New wait (15).
	db 15	;   Escape wait value.
	db 1	;    Reset effect, with inverted volume: 0.
	db 22	;    Arpeggio table effect 1.
	db 12	; Note with effects flag.
	db 197	; Note reference (5). New wait (127).
	db 127	;   Escape wait value.
	db 1	;    Reset effect, with inverted volume: 0.
	db 38	;    Arpeggio table effect 2.

ALIENALL_Subsong0_Track11
	db 241	; New instrument (5). Note reference (1). New wait (9).
	db 5	;   Escape instrument value.
	db 9	;   Escape wait value.
	db 131	; Note reference (3). Secondary wait (1).
	db 130	; Note reference (2). Secondary wait (1).
	db 74	; Note reference (10). Primary wait (0).
	db 203	; Note reference (11). New wait (127).
	db 127	;   Escape wait value.

ALIENALL_Subsong0_Track12
	db 12	; Note with effects flag.
	db 201	; Note reference (9). New wait (15).
	db 15	;   Escape wait value.
	db 1	;    Reset effect, with inverted volume: 0.
	db 54	;    Arpeggio table effect 3.
	db 12	; Note with effects flag.
	db 193	; Note reference (1). New wait (7).
	db 7	;   Escape wait value.
	db 1	;    Reset effect, with inverted volume: 0.
	db 22	;    Arpeggio table effect 1.
	db 12	; Note with effects flag.
	db 197	; Note reference (5). New wait (127).
	db 127	;   Escape wait value.
	db 1	;    Reset effect, with inverted volume: 0.
	db 54	;    Arpeggio table effect 3.

ALIENALL_Subsong0_Track13
	db 254	; New instrument (5). New escaped note: 66. New wait (5).
	db 66	;   Escape note value.
	db 5	;   Escape instrument value.
	db 5	;   Escape wait value.
	db 11	; Note reference (11). 
	db 202	; Note reference (10). New wait (3).
	db 3	;   Escape wait value.
	db 130	; Note reference (2). Secondary wait (1).
	db 138	; Note reference (10). Secondary wait (1).
	db 130	; Note reference (2). Secondary wait (1).
	db 195	; Note reference (3). New wait (127).
	db 127	;   Escape wait value.

ALIENALL_Subsong0_Track14
	db 254	; New instrument (5). New escaped note: 69. New wait (15).
	db 69	;   Escape note value.
	db 5	;   Escape instrument value.
	db 15	;   Escape wait value.
	db 206	; New escaped note: 71. New wait (127).
	db 71	;   Escape note value.
	db 127	;   Escape wait value.

ALIENALL_Subsong0_Track15
	db 12	; Note with effects flag.
	db 145	; Primary instrument (1). Note reference (1). Secondary wait (1).
	db 2	;    Volume effect, with inverted volume: 0.
	db 87	; Primary instrument (1). Note reference (7). Primary wait (0).
	db 12	; Note with effects flag.
	db 81	; Primary instrument (1). Note reference (1). Primary wait (0).
	db 50	;    Volume effect, with inverted volume: 3.
	db 12	; Note with effects flag.
	db 82	; Primary instrument (1). Note reference (2). Primary wait (0).
	db 2	;    Volume effect, with inverted volume: 0.
	db 12	; Note with effects flag.
	db 87	; Primary instrument (1). Note reference (7). Primary wait (0).
	db 50	;    Volume effect, with inverted volume: 3.
	db 12	; Note with effects flag.
	db 87	; Primary instrument (1). Note reference (7). Primary wait (0).
	db 2	;    Volume effect, with inverted volume: 0.
	db 12	; Note with effects flag.
	db 82	; Primary instrument (1). Note reference (2). Primary wait (0).
	db 50	;    Volume effect, with inverted volume: 3.
	db 12	; Note with effects flag.
	db 81	; Primary instrument (1). Note reference (1). Primary wait (0).
	db 2	;    Volume effect, with inverted volume: 0.
	db 12	; Note with effects flag.
	db 87	; Primary instrument (1). Note reference (7). Primary wait (0).
	db 50	;    Volume effect, with inverted volume: 3.
	db 12	; Note with effects flag.
	db 87	; Primary instrument (1). Note reference (7). Primary wait (0).
	db 2	;    Volume effect, with inverted volume: 0.
	db 12	; Note with effects flag.
	db 81	; Primary instrument (1). Note reference (1). Primary wait (0).
	db 50	;    Volume effect, with inverted volume: 3.
	db 12	; Note with effects flag.
	db 82	; Primary instrument (1). Note reference (2). Primary wait (0).
	db 2	;    Volume effect, with inverted volume: 0.
	db 12	; Note with effects flag.
	db 87	; Primary instrument (1). Note reference (7). Primary wait (0).
	db 50	;    Volume effect, with inverted volume: 3.
	db 12	; Note with effects flag.
	db 87	; Primary instrument (1). Note reference (7). Primary wait (0).
	db 2	;    Volume effect, with inverted volume: 0.
	db 12	; Note with effects flag.
	db 82	; Primary instrument (1). Note reference (2). Primary wait (0).
	db 50	;    Volume effect, with inverted volume: 3.
	db 12	; Note with effects flag.
	db 83	; Primary instrument (1). Note reference (3). Primary wait (0).
	db 2	;    Volume effect, with inverted volume: 0.
	db 12	; Note with effects flag.
	db 87	; Primary instrument (1). Note reference (7). Primary wait (0).
	db 50	;    Volume effect, with inverted volume: 3.
	db 12	; Note with effects flag.
	db 82	; Primary instrument (1). Note reference (2). Primary wait (0).
	db 2	;    Volume effect, with inverted volume: 0.
	db 12	; Note with effects flag.
	db 83	; Primary instrument (1). Note reference (3). Primary wait (0).
	db 50	;    Volume effect, with inverted volume: 3.
	db 12	; Note with effects flag.
	db 83	; Primary instrument (1). Note reference (3). Primary wait (0).
	db 2	;    Volume effect, with inverted volume: 0.
	db 12	; Note with effects flag.
	db 82	; Primary instrument (1). Note reference (2). Primary wait (0).
	db 50	;    Volume effect, with inverted volume: 3.
	db 12	; Note with effects flag.
	db 81	; Primary instrument (1). Note reference (1). Primary wait (0).
	db 2	;    Volume effect, with inverted volume: 0.
	db 85	; Primary instrument (1). Note reference (5). Primary wait (0).
	db 12	; Note with effects flag.
	db 82	; Primary instrument (1). Note reference (2). Primary wait (0).
	db 82	;    Volume effect, with inverted volume: 5.
	db 12	; Note with effects flag.
	db 85	; Primary instrument (1). Note reference (5). Primary wait (0).
	db 2	;    Volume effect, with inverted volume: 0.
	db 145	; Primary instrument (1). Note reference (1). Secondary wait (1).
	db 83	; Primary instrument (1). Note reference (3). Primary wait (0).
	db 12	; Note with effects flag.
	db 81	; Primary instrument (1). Note reference (1). Primary wait (0).
	db 50	;    Volume effect, with inverted volume: 3.
	db 12	; Note with effects flag.
	db 85	; Primary instrument (1). Note reference (5). Primary wait (0).
	db 2	;    Volume effect, with inverted volume: 0.
	db 12	; Note with effects flag.
	db 211	; Primary instrument (1). Note reference (3). New wait (127).
	db 127	;   Escape wait value.
	db 50	;    Volume effect, with inverted volume: 3.

ALIENALL_Subsong0_Track16
	db 12	; Note with effects flag.
	db 217	; Primary instrument (1). Note reference (9). New wait (2).
	db 2	;   Escape wait value.
	db 2	;    Volume effect, with inverted volume: 0.
	db 12	; Note with effects flag.
	db 25	; Primary instrument (1). Note reference (9). 
	db 50	;    Volume effect, with inverted volume: 3.
	db 12	; Note with effects flag.
	db 153	; Primary instrument (1). Note reference (9). Secondary wait (1).
	db 82	;    Volume effect, with inverted volume: 5.
	db 12	; Note with effects flag.
	db 154	; Primary instrument (1). Note reference (10). Secondary wait (1).
	db 2	;    Volume effect, with inverted volume: 0.
	db 82	; Primary instrument (1). Note reference (2). Primary wait (0).
	db 12	; Note with effects flag.
	db 90	; Primary instrument (1). Note reference (10). Primary wait (0).
	db 50	;    Volume effect, with inverted volume: 3.
	db 12	; Note with effects flag.
	db 83	; Primary instrument (1). Note reference (3). Primary wait (0).
	db 2	;    Volume effect, with inverted volume: 0.
	db 12	; Note with effects flag.
	db 82	; Primary instrument (1). Note reference (2). Primary wait (0).
	db 50	;    Volume effect, with inverted volume: 3.
	db 12	; Note with effects flag.
	db 81	; Primary instrument (1). Note reference (1). Primary wait (0).
	db 2	;    Volume effect, with inverted volume: 0.
	db 83	; Primary instrument (1). Note reference (3). Primary wait (0).
	db 12	; Note with effects flag.
	db 82	; Primary instrument (1). Note reference (2). Primary wait (0).
	db 82	;    Volume effect, with inverted volume: 5.
	db 12	; Note with effects flag.
	db 81	; Primary instrument (1). Note reference (1). Primary wait (0).
	db 50	;    Volume effect, with inverted volume: 3.
	db 147	; Primary instrument (1). Note reference (3). Secondary wait (1).
	db 12	; Note with effects flag.
	db 81	; Primary instrument (1). Note reference (1). Primary wait (0).
	db 82	;    Volume effect, with inverted volume: 5.
	db 211	; Primary instrument (1). Note reference (3). New wait (127).
	db 127	;   Escape wait value.

ALIENALL_Subsong0_Track17
	db 12	; Note with effects flag.
	db 217	; Primary instrument (1). Note reference (9). New wait (2).
	db 2	;   Escape wait value.
	db 2	;    Volume effect, with inverted volume: 0.
	db 12	; Note with effects flag.
	db 25	; Primary instrument (1). Note reference (9). 
	db 50	;    Volume effect, with inverted volume: 3.
	db 12	; Note with effects flag.
	db 153	; Primary instrument (1). Note reference (9). Secondary wait (1).
	db 82	;    Volume effect, with inverted volume: 5.
	db 12	; Note with effects flag.
	db 154	; Primary instrument (1). Note reference (10). Secondary wait (1).
	db 2	;    Volume effect, with inverted volume: 0.
	db 82	; Primary instrument (1). Note reference (2). Primary wait (0).
	db 12	; Note with effects flag.
	db 90	; Primary instrument (1). Note reference (10). Primary wait (0).
	db 50	;    Volume effect, with inverted volume: 3.
	db 12	; Note with effects flag.
	db 83	; Primary instrument (1). Note reference (3). Primary wait (0).
	db 2	;    Volume effect, with inverted volume: 0.
	db 12	; Note with effects flag.
	db 82	; Primary instrument (1). Note reference (2). Primary wait (0).
	db 50	;    Volume effect, with inverted volume: 3.
	db 12	; Note with effects flag.
	db 81	; Primary instrument (1). Note reference (1). Primary wait (0).
	db 2	;    Volume effect, with inverted volume: 0.
	db 91	; Primary instrument (1). Note reference (11). Primary wait (0).
	db 12	; Note with effects flag.
	db 82	; Primary instrument (1). Note reference (2). Primary wait (0).
	db 82	;    Volume effect, with inverted volume: 5.
	db 12	; Note with effects flag.
	db 81	; Primary instrument (1). Note reference (1). Primary wait (0).
	db 50	;    Volume effect, with inverted volume: 3.
	db 155	; Primary instrument (1). Note reference (11). Secondary wait (1).
	db 12	; Note with effects flag.
	db 81	; Primary instrument (1). Note reference (1). Primary wait (0).
	db 82	;    Volume effect, with inverted volume: 5.
	db 219	; Primary instrument (1). Note reference (11). New wait (127).
	db 127	;   Escape wait value.

ALIENALL_Subsong0_Track18
	db 12	; Note with effects flag.
	db 96	; Secondary instrument (7). Note reference (0). Primary wait (0).
	db 0	;    Reset effect, with inverted volume: 0.
	db 246	; New instrument (9). Note reference (6). New wait (2).
	db 9	;   Escape instrument value.
	db 2	;   Escape wait value.
	db 120	; New instrument (8). Note reference (8). Primary wait (0).
	db 8	;   Escape instrument value.
	db 118	; New instrument (9). Note reference (6). Primary wait (0).
	db 9	;   Escape instrument value.
	db 96	; Secondary instrument (7). Note reference (0). Primary wait (0).
	db 70	; Note reference (6). Primary wait (0).
	db 96	; Secondary instrument (7). Note reference (0). Primary wait (0).
	db 70	; Note reference (6). Primary wait (0).
	db 96	; Secondary instrument (7). Note reference (0). Primary wait (0).
	db 96	; Secondary instrument (7). Note reference (0). Primary wait (0).
	db 120	; New instrument (8). Note reference (8). Primary wait (0).
	db 8	;   Escape instrument value.
	db 118	; New instrument (9). Note reference (6). Primary wait (0).
	db 9	;   Escape instrument value.
	db 96	; Secondary instrument (7). Note reference (0). Primary wait (0).
	db 70	; Note reference (6). Primary wait (0).
	db 96	; Secondary instrument (7). Note reference (0). Primary wait (0).
	db 4	; Note reference (4). 
	db 120	; New instrument (8). Note reference (8). Primary wait (0).
	db 8	;   Escape instrument value.
	db 116	; New instrument (9). Note reference (4). Primary wait (0).
	db 9	;   Escape instrument value.
	db 110	; Secondary instrument (7). New escaped note: 43. Primary wait (0).
	db 43	;   Escape note value.
	db 111	; Secondary instrument (7). Same escaped note: 43. Primary wait (0).
	db 110	; Secondary instrument (7). New escaped note: 40. Primary wait (0).
	db 40	;   Escape note value.
	db 111	; Secondary instrument (7). Same escaped note: 40. Primary wait (0).
	db 68	; Note reference (4). Primary wait (0).
	db 110	; Secondary instrument (7). New escaped note: 38. Primary wait (0).
	db 38	;   Escape note value.
	db 111	; Secondary instrument (7). Same escaped note: 38. Primary wait (0).
	db 68	; Note reference (4). Primary wait (0).
	db 96	; Secondary instrument (7). Note reference (0). Primary wait (0).
	db 196	; Note reference (4). New wait (127).
	db 127	;   Escape wait value.

ALIENALL_Subsong0_Track19
	db 12	; Note with effects flag.
	db 193	; Note reference (1). New wait (15).
	db 15	;   Escape wait value.
	db 1	;    Reset effect, with inverted volume: 0.
	db 22	;    Arpeggio table effect 1.
	db 12	; Note with effects flag.
	db 195	; Note reference (3). New wait (127).
	db 127	;   Escape wait value.
	db 1	;    Reset effect, with inverted volume: 0.
	db 70	;    Arpeggio table effect 4.

ALIENALL_Subsong0_Track20
	db 12	; Note with effects flag.
	db 81	; Primary instrument (1). Note reference (1). Primary wait (0).
	db 2	;    Volume effect, with inverted volume: 0.
	db 12	; Note with effects flag.
	db 83	; Primary instrument (1). Note reference (3). Primary wait (0).
	db 50	;    Volume effect, with inverted volume: 3.
	db 12	; Note with effects flag.
	db 82	; Primary instrument (1). Note reference (2). Primary wait (0).
	db 2	;    Volume effect, with inverted volume: 0.
	db 12	; Note with effects flag.
	db 81	; Primary instrument (1). Note reference (1). Primary wait (0).
	db 50	;    Volume effect, with inverted volume: 3.
	db 12	; Note with effects flag.
	db 91	; Primary instrument (1). Note reference (11). Primary wait (0).
	db 2	;    Volume effect, with inverted volume: 0.
	db 12	; Note with effects flag.
	db 82	; Primary instrument (1). Note reference (2). Primary wait (0).
	db 50	;    Volume effect, with inverted volume: 3.
	db 12	; Note with effects flag.
	db 82	; Primary instrument (1). Note reference (2). Primary wait (0).
	db 2	;    Volume effect, with inverted volume: 0.
	db 12	; Note with effects flag.
	db 91	; Primary instrument (1). Note reference (11). Primary wait (0).
	db 50	;    Volume effect, with inverted volume: 3.
	db 12	; Note with effects flag.
	db 81	; Primary instrument (1). Note reference (1). Primary wait (0).
	db 2	;    Volume effect, with inverted volume: 0.
	db 12	; Note with effects flag.
	db 82	; Primary instrument (1). Note reference (2). Primary wait (0).
	db 50	;    Volume effect, with inverted volume: 3.
	db 12	; Note with effects flag.
	db 82	; Primary instrument (1). Note reference (2). Primary wait (0).
	db 2	;    Volume effect, with inverted volume: 0.
	db 12	; Note with effects flag.
	db 81	; Primary instrument (1). Note reference (1). Primary wait (0).
	db 50	;    Volume effect, with inverted volume: 3.
	db 12	; Note with effects flag.
	db 91	; Primary instrument (1). Note reference (11). Primary wait (0).
	db 2	;    Volume effect, with inverted volume: 0.
	db 12	; Note with effects flag.
	db 82	; Primary instrument (1). Note reference (2). Primary wait (0).
	db 50	;    Volume effect, with inverted volume: 3.
	db 12	; Note with effects flag.
	db 82	; Primary instrument (1). Note reference (2). Primary wait (0).
	db 2	;    Volume effect, with inverted volume: 0.
	db 12	; Note with effects flag.
	db 91	; Primary instrument (1). Note reference (11). Primary wait (0).
	db 50	;    Volume effect, with inverted volume: 3.
	db 12	; Note with effects flag.
	db 87	; Primary instrument (1). Note reference (7). Primary wait (0).
	db 2	;    Volume effect, with inverted volume: 0.
	db 12	; Note with effects flag.
	db 82	; Primary instrument (1). Note reference (2). Primary wait (0).
	db 50	;    Volume effect, with inverted volume: 3.
	db 12	; Note with effects flag.
	db 85	; Primary instrument (1). Note reference (5). Primary wait (0).
	db 2	;    Volume effect, with inverted volume: 0.
	db 12	; Note with effects flag.
	db 87	; Primary instrument (1). Note reference (7). Primary wait (0).
	db 50	;    Volume effect, with inverted volume: 3.
	db 12	; Note with effects flag.
	db 83	; Primary instrument (1). Note reference (3). Primary wait (0).
	db 2	;    Volume effect, with inverted volume: 0.
	db 12	; Note with effects flag.
	db 85	; Primary instrument (1). Note reference (5). Primary wait (0).
	db 50	;    Volume effect, with inverted volume: 3.
	db 12	; Note with effects flag.
	db 85	; Primary instrument (1). Note reference (5). Primary wait (0).
	db 2	;    Volume effect, with inverted volume: 0.
	db 12	; Note with effects flag.
	db 83	; Primary instrument (1). Note reference (3). Primary wait (0).
	db 50	;    Volume effect, with inverted volume: 3.
	db 12	; Note with effects flag.
	db 83	; Primary instrument (1). Note reference (3). Primary wait (0).
	db 2	;    Volume effect, with inverted volume: 0.
	db 12	; Note with effects flag.
	db 85	; Primary instrument (1). Note reference (5). Primary wait (0).
	db 50	;    Volume effect, with inverted volume: 3.
	db 12	; Note with effects flag.
	db 82	; Primary instrument (1). Note reference (2). Primary wait (0).
	db 2	;    Volume effect, with inverted volume: 0.
	db 12	; Note with effects flag.
	db 83	; Primary instrument (1). Note reference (3). Primary wait (0).
	db 50	;    Volume effect, with inverted volume: 3.
	db 12	; Note with effects flag.
	db 83	; Primary instrument (1). Note reference (3). Primary wait (0).
	db 2	;    Volume effect, with inverted volume: 0.
	db 12	; Note with effects flag.
	db 82	; Primary instrument (1). Note reference (2). Primary wait (0).
	db 50	;    Volume effect, with inverted volume: 3.
	db 12	; Note with effects flag.
	db 85	; Primary instrument (1). Note reference (5). Primary wait (0).
	db 2	;    Volume effect, with inverted volume: 0.
	db 12	; Note with effects flag.
	db 211	; Primary instrument (1). Note reference (3). New wait (127).
	db 127	;   Escape wait value.
	db 50	;    Volume effect, with inverted volume: 3.

ALIENALL_Subsong0_Track21
	db 12	; Note with effects flag.
	db 202	; Note reference (10). New wait (15).
	db 15	;   Escape wait value.
	db 1	;    Reset effect, with inverted volume: 0.
	db 22	;    Arpeggio table effect 1.
	db 12	; Note with effects flag.
	db 203	; Note reference (11). New wait (127).
	db 127	;   Escape wait value.
	db 1	;    Reset effect, with inverted volume: 0.
	db 22	;    Arpeggio table effect 1.

ALIENALL_Subsong0_Track22
	db 12	; Note with effects flag.
	db 89	; Primary instrument (1). Note reference (9). Primary wait (0).
	db 2	;    Volume effect, with inverted volume: 0.
	db 12	; Note with effects flag.
	db 85	; Primary instrument (1). Note reference (5). Primary wait (0).
	db 50	;    Volume effect, with inverted volume: 3.
	db 12	; Note with effects flag.
	db 81	; Primary instrument (1). Note reference (1). Primary wait (0).
	db 2	;    Volume effect, with inverted volume: 0.
	db 12	; Note with effects flag.
	db 89	; Primary instrument (1). Note reference (9). Primary wait (0).
	db 50	;    Volume effect, with inverted volume: 3.
	db 12	; Note with effects flag.
	db 90	; Primary instrument (1). Note reference (10). Primary wait (0).
	db 2	;    Volume effect, with inverted volume: 0.
	db 12	; Note with effects flag.
	db 81	; Primary instrument (1). Note reference (1). Primary wait (0).
	db 50	;    Volume effect, with inverted volume: 3.
	db 12	; Note with effects flag.
	db 81	; Primary instrument (1). Note reference (1). Primary wait (0).
	db 2	;    Volume effect, with inverted volume: 0.
	db 12	; Note with effects flag.
	db 90	; Primary instrument (1). Note reference (10). Primary wait (0).
	db 50	;    Volume effect, with inverted volume: 3.
	db 12	; Note with effects flag.
	db 89	; Primary instrument (1). Note reference (9). Primary wait (0).
	db 2	;    Volume effect, with inverted volume: 0.
	db 12	; Note with effects flag.
	db 81	; Primary instrument (1). Note reference (1). Primary wait (0).
	db 50	;    Volume effect, with inverted volume: 3.
	db 12	; Note with effects flag.
	db 81	; Primary instrument (1). Note reference (1). Primary wait (0).
	db 2	;    Volume effect, with inverted volume: 0.
	db 12	; Note with effects flag.
	db 89	; Primary instrument (1). Note reference (9). Primary wait (0).
	db 50	;    Volume effect, with inverted volume: 3.
	db 12	; Note with effects flag.
	db 90	; Primary instrument (1). Note reference (10). Primary wait (0).
	db 2	;    Volume effect, with inverted volume: 0.
	db 12	; Note with effects flag.
	db 81	; Primary instrument (1). Note reference (1). Primary wait (0).
	db 50	;    Volume effect, with inverted volume: 3.
	db 12	; Note with effects flag.
	db 81	; Primary instrument (1). Note reference (1). Primary wait (0).
	db 2	;    Volume effect, with inverted volume: 0.
	db 12	; Note with effects flag.
	db 90	; Primary instrument (1). Note reference (10). Primary wait (0).
	db 50	;    Volume effect, with inverted volume: 3.
	db 12	; Note with effects flag.
	db 83	; Primary instrument (1). Note reference (3). Primary wait (0).
	db 2	;    Volume effect, with inverted volume: 0.
	db 12	; Note with effects flag.
	db 81	; Primary instrument (1). Note reference (1). Primary wait (0).
	db 50	;    Volume effect, with inverted volume: 3.
	db 12	; Note with effects flag.
	db 81	; Primary instrument (1). Note reference (1). Primary wait (0).
	db 2	;    Volume effect, with inverted volume: 0.
	db 12	; Note with effects flag.
	db 83	; Primary instrument (1). Note reference (3). Primary wait (0).
	db 50	;    Volume effect, with inverted volume: 3.
	db 12	; Note with effects flag.
	db 85	; Primary instrument (1). Note reference (5). Primary wait (0).
	db 2	;    Volume effect, with inverted volume: 0.
	db 12	; Note with effects flag.
	db 81	; Primary instrument (1). Note reference (1). Primary wait (0).
	db 50	;    Volume effect, with inverted volume: 3.
	db 12	; Note with effects flag.
	db 81	; Primary instrument (1). Note reference (1). Primary wait (0).
	db 2	;    Volume effect, with inverted volume: 0.
	db 12	; Note with effects flag.
	db 85	; Primary instrument (1). Note reference (5). Primary wait (0).
	db 50	;    Volume effect, with inverted volume: 3.
	db 12	; Note with effects flag.
	db 83	; Primary instrument (1). Note reference (3). Primary wait (0).
	db 2	;    Volume effect, with inverted volume: 0.
	db 12	; Note with effects flag.
	db 81	; Primary instrument (1). Note reference (1). Primary wait (0).
	db 50	;    Volume effect, with inverted volume: 3.
	db 12	; Note with effects flag.
	db 81	; Primary instrument (1). Note reference (1). Primary wait (0).
	db 2	;    Volume effect, with inverted volume: 0.
	db 12	; Note with effects flag.
	db 83	; Primary instrument (1). Note reference (3). Primary wait (0).
	db 50	;    Volume effect, with inverted volume: 3.
	db 12	; Note with effects flag.
	db 85	; Primary instrument (1). Note reference (5). Primary wait (0).
	db 2	;    Volume effect, with inverted volume: 0.
	db 12	; Note with effects flag.
	db 81	; Primary instrument (1). Note reference (1). Primary wait (0).
	db 50	;    Volume effect, with inverted volume: 3.
	db 12	; Note with effects flag.
	db 83	; Primary instrument (1). Note reference (3). Primary wait (0).
	db 2	;    Volume effect, with inverted volume: 0.
	db 12	; Note with effects flag.
	db 213	; Primary instrument (1). Note reference (5). New wait (127).
	db 127	;   Escape wait value.
	db 50	;    Volume effect, with inverted volume: 3.

ALIENALL_Subsong0_Track23
	db 242	; New instrument (4). Note reference (2). New wait (3).
	db 4	;   Escape instrument value.
	db 3	;   Escape wait value.
	db 2	; Note reference (2). 
	db 130	; Note reference (2). Secondary wait (1).
	db 74	; Note reference (10). Primary wait (0).
	db 194	; Note reference (2). New wait (2).
	db 2	;   Escape wait value.
	db 129	; Note reference (1). Secondary wait (1).
	db 195	; Note reference (3). New wait (7).
	db 7	;   Escape wait value.
	db 129	; Note reference (1). Secondary wait (1).
	db 133	; Note reference (5). Secondary wait (1).
	db 73	; Note reference (9). Primary wait (0).
	db 197	; Note reference (5). New wait (127).
	db 127	;   Escape wait value.

ALIENALL_Subsong0_Track24
	db 249	; New instrument (4). Note reference (9). New wait (5).
	db 4	;   Escape instrument value.
	db 5	;   Escape wait value.
	db 5	; Note reference (5). 
	db 193	; Note reference (1). New wait (3).
	db 3	;   Escape wait value.
	db 194	; Note reference (2). New wait (5).
	db 5	;   Escape wait value.
	db 195	; Note reference (3). New wait (127).
	db 127	;   Escape wait value.

ALIENALL_Subsong0_Track25
	db 249	; New instrument (4). Note reference (9). New wait (5).
	db 4	;   Escape instrument value.
	db 5	;   Escape wait value.
	db 5	; Note reference (5). 
	db 193	; Note reference (1). New wait (3).
	db 3	;   Escape wait value.
	db 206	; New escaped note: 66. New wait (5).
	db 66	;   Escape note value.
	db 5	;   Escape wait value.
	db 203	; Note reference (11). New wait (127).
	db 127	;   Escape wait value.

ALIENALL_Subsong0_Track26
	db 12	; Note with effects flag.
	db 96	; Secondary instrument (7). Note reference (0). Primary wait (0).
	db 0	;    Reset effect, with inverted volume: 0.
	db 246	; New instrument (9). Note reference (6). New wait (2).
	db 9	;   Escape instrument value.
	db 2	;   Escape wait value.
	db 120	; New instrument (8). Note reference (8). Primary wait (0).
	db 8	;   Escape instrument value.
	db 118	; New instrument (9). Note reference (6). Primary wait (0).
	db 9	;   Escape instrument value.
	db 96	; Secondary instrument (7). Note reference (0). Primary wait (0).
	db 70	; Note reference (6). Primary wait (0).
	db 96	; Secondary instrument (7). Note reference (0). Primary wait (0).
	db 70	; Note reference (6). Primary wait (0).
	db 96	; Secondary instrument (7). Note reference (0). Primary wait (0).
	db 96	; Secondary instrument (7). Note reference (0). Primary wait (0).
	db 120	; New instrument (8). Note reference (8). Primary wait (0).
	db 8	;   Escape instrument value.
	db 118	; New instrument (9). Note reference (6). Primary wait (0).
	db 9	;   Escape instrument value.
	db 96	; Secondary instrument (7). Note reference (0). Primary wait (0).
	db 70	; Note reference (6). Primary wait (0).
	db 96	; Secondary instrument (7). Note reference (0). Primary wait (0).
	db 4	; Note reference (4). 
	db 120	; New instrument (8). Note reference (8). Primary wait (0).
	db 8	;   Escape instrument value.
	db 116	; New instrument (9). Note reference (4). Primary wait (0).
	db 9	;   Escape instrument value.
	db 96	; Secondary instrument (7). Note reference (0). Primary wait (0).
	db 68	; Note reference (4). Primary wait (0).
	db 96	; Secondary instrument (7). Note reference (0). Primary wait (0).
	db 68	; Note reference (4). Primary wait (0).
	db 110	; Secondary instrument (7). New escaped note: 43. Primary wait (0).
	db 43	;   Escape note value.
	db 110	; Secondary instrument (7). New escaped note: 41. Primary wait (0).
	db 41	;   Escape note value.
	db 110	; Secondary instrument (7). New escaped note: 40. Primary wait (0).
	db 40	;   Escape note value.
	db 110	; Secondary instrument (7). New escaped note: 38. Primary wait (0).
	db 38	;   Escape note value.
	db 96	; Secondary instrument (7). Note reference (0). Primary wait (0).
	db 224	; Secondary instrument (7). Note reference (0). New wait (127).
	db 127	;   Escape wait value.

ALIENALL_Subsong0DisarkByteRegionEnd5
; The note indexes.
ALIENALL_Subsong0_NoteIndexes
ALIENALL_Subsong0DisarkByteRegionStart6
	db 36	; Note for index 0.
	db 57	; Note for index 1.
	db 61	; Note for index 2.
	db 59	; Note for index 3.
	db 28	; Note for index 4.
	db 56	; Note for index 5.
	db 26	; Note for index 6.
	db 52	; Note for index 7.
	db 48	; Note for index 8.
	db 54	; Note for index 9.
	db 62	; Note for index 10.
	db 64	; Note for index 11.
ALIENALL_Subsong0DisarkByteRegionEnd6

; ALIENALL, Subsong 1.
; ----------------------------------

ALIENALL_Subsong1
ALIENALL_Subsong1DisarkPointerRegionStart0
	dw ALIENALL_Subsong1_NoteIndexes	; Index table for the notes.
	dw ALIENALL_Subsong1_TrackIndexes	; Index table for the Tracks.
ALIENALL_Subsong1DisarkPointerRegionEnd0

ALIENALL_Subsong1DisarkByteRegionStart1
	db 6	; Initial speed.

	db 1	; Most used instrument.
	db 7	; Second most used instrument.

	db 0	; Most used wait.
	db 1	; Second most used wait.

	db 0	; Default start note in tracks.
	db 0	; Default start instrument in tracks.
	db 0	; Default start wait in tracks.

	db 12	; Are there effects? 12 if yes, 13 if not. Don't ask.
ALIENALL_Subsong1DisarkByteRegionEnd1

; The Linker.
ALIENALL_Subsong1DisarkByteRegionStart2
; Pattern 0
ALIENALL_Subsong1_Loop
	db 170	; State byte.
	db 63	; New height.
	db 128	; New track (0) for channel 1, as a reference (index 0).
	db 128	; New track (0) for channel 2, as a reference (index 0).
	db 128	; New track (0) for channel 3, as a reference (index 0).

	db 1	; End of the Song.
	db 0	; Speed to 0, meaning "end of song".
ALIENALL_Subsong1DisarkByteRegionEnd2
ALIENALL_Subsong1DisarkPointerRegionStart3
	dw ALIENALL_Subsong1_Loop

ALIENALL_Subsong1DisarkPointerRegionEnd3
; The indexes of the tracks.
ALIENALL_Subsong1_TrackIndexes
ALIENALL_Subsong1DisarkPointerRegionStart4
	dw ALIENALL_Subsong1_Track0	; Track 0, index 0.
ALIENALL_Subsong1DisarkPointerRegionEnd4

ALIENALL_Subsong1DisarkByteRegionStart5
ALIENALL_Subsong1_Track0
	db 205	; New wait (127).
	db 127	;   Escape wait value.

ALIENALL_Subsong1DisarkByteRegionEnd5
; The note indexes.
ALIENALL_Subsong1_NoteIndexes
ALIENALL_Subsong1DisarkByteRegionStart6
	db 36	; Note for index 0.
	db 57	; Note for index 1.
	db 61	; Note for index 2.
	db 59	; Note for index 3.
	db 28	; Note for index 4.
	db 56	; Note for index 5.
	db 26	; Note for index 6.
	db 52	; Note for index 7.
	db 48	; Note for index 8.
	db 54	; Note for index 9.
	db 62	; Note for index 10.
	db 64	; Note for index 11.
ALIENALL_Subsong1DisarkByteRegionEnd6

