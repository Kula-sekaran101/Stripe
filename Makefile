.PHONY: clean All

All:
	@echo "==========Building project:[ BraceExpansion - Debug ]=========="
	@cd "BraceExpansion" && "$(MAKE)" -f  "BraceExpansion.mk"
clean:
	@echo "==========Cleaning project:[ BraceExpansion - Debug ]----------"
	@cd "BraceExpansion" && "$(MAKE)" -f  "BraceExpansion.mk" clean
