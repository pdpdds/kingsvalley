OUTPUT := ../generated
GENERATED := $(OUTPUT)/tiles.h $(OUTPUT)/title.h $(OUTPUT)/playermove.h $(OUTPUT)/playerknife.h $(OUTPUT)/playerpickax.h $(OUTPUT)/playerattack.h $(OUTPUT)/playerdigging.h $(OUTPUT)/enemy.h $(OUTPUT)/knife.h $(OUTPUT)/map.h $(OUTPUT)/map_summary.h

all: $(GENERATED)

$(OUTPUT)/tiles.h: tiles.png
	python ../tools/png2tiles.py -i tiles $< > $@

$(OUTPUT)/title.h: tiles.png
	python ../tools/png2tiles.py -i title $< > $@	

$(OUTPUT)/playermove.h: playermove.png
	python ../tools/png2sprites.py -i playermove_sprite $< > $@
	
$(OUTPUT)/playerknife.h: playerknife.png
	python ../tools/png2sprites.py -i playerknife_sprite $< > $@

$(OUTPUT)/playerpickax.h: playerpickax.png
	python ../tools/png2sprites.py -i playerpickax_sprite $< > $@	
	
$(OUTPUT)/playerattack.h: playerattack.png
	python ../tools/png2sprites.py -i playerattack_sprite $< > $@	

$(OUTPUT)/playerdigging.h: playerdigging.png
	python ../tools/png2sprites.py -i playerdigging_sprite $< > $@		
	
$(OUTPUT)/enemy.h: enemy.png
	python ../tools/png2sprites.py -i enemy_sprite $< > $@
	
$(OUTPUT)/knife.h: knife.png
	python ../tools/png2sprites.py -i knife_sprite $< > $@
	

$(OUTPUT)/map.h:
	python ../tools/map_generate.py > $@

$(OUTPUT)/map_summary.h:
	python ../tools/map_summary.py map_summary > $@

.PHONY: all clean
clean:
	rm -f $(OUTPUT)/*

