.PHONY: clean All

All:
	@echo "==========Building project:[ 1087 - Debug ]=========="
	@cd "1087" && "$(MAKE)" -f  "1087.mk"
clean:
	@echo "==========Cleaning project:[ 1087 - Debug ]----------"
	@cd "1087" && "$(MAKE)" -f  "1087.mk" clean
