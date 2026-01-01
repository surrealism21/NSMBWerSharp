.text

.global ReturnNone
ReturnNone:
	blr

.global ReturnTrue
ReturnTrue:
	li r3, 1
	blr

.global ReturnFalse
ReturnFalse:
	li r3, 0
	blr

# a sub so it makes sense
.global CheckExistingPowerup
CheckExistingPowerup:

	lwz r3, 0x14E0(r3)
	blr