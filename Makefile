.PHONY: debug clean replace

debug: replace
	$(MAKE) -f QwopBot.mk

replace:
	sed -i 's/\/home\/matteo\/Progetti\/QwopBot\///g' QwopBot.mk

clean: replace 
	$(MAKE) -f QwopBot.mk clean
