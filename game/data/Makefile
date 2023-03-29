OUTPUT := ../generated
GENERATED := $(OUTPUT)/tiles.h $(OUTPUT)/title.h $(OUTPUT)/playermove.h $(OUTPUT)/playerknife.h $(OUTPUT)/playerpickax.h $(OUTPUT)/playerattack.h $(OUTPUT)/playerdigging.h $(OUTPUT)/enemy.h $(OUTPUT)/knife.h $(OUTPUT)/door.h $(OUTPUT)/map.h $(OUTPUT)/map_summary.h

all: $(GENERATED)

$(OUTPUT)/tiles.h: tiles.png
	python ../tools/png2tiles.py -i tiles $< > $@

$(OUTPUT)/title.h: tiles.png
	python ../tools/png2tiles.py -i title $< > $@	

$(OUTPUT)/playermove.h: p_move.png
	python ../tools/png2sprites.py -i playermove_sprite $< > $@
	
$(OUTPUT)/playerknife.h: p_knife.png
	python ../tools/png2sprites.py -i playerknife_sprite $< > $@

$(OUTPUT)/playerpickax.h: p_pickax.png
	python ../tools/png2sprites.py -i playerpickax_sprite $< > $@	
	
$(OUTPUT)/playerattack.h: p_attack.png
	python ../tools/png2sprites.py -i playerattack_sprite $< > $@	

$(OUTPUT)/playerdigging.h: p_dig.png
	python ../tools/png2sprites.py -i playerdigging_sprite $< > $@		
	
$(OUTPUT)/enemy.h: enemy.png
	python ../tools/png2sprites.py -i enemy_sprite $< > $@
	
$(OUTPUT)/knife.h: knife.png
	python ../tools/png2sprites.py -i knife_sprite $< > $@
	
$(OUTPUT)/door.h: gate.png
	python ../tools/png2sprites.py -i door_sprite $< > $@
	

$(OUTPUT)/map.h:
	python ../tools/map_generate.py > $@

$(OUTPUT)/map_summary.h:
	python ../tools/map_summary.py map_summary > $@

.PHONY: all clean
clean:
	rm -f $(OUTPUT)/*

