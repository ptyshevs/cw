# #

#
  	.comment	"Baby don't hurt me"

  	.name		"What is love"

live %-1
gohere: ld %80, r2
ld %97, r3
st r3, 0
aff r2
aff r3
add r1, r1, r2
fork %:high
fork %:high
fork %:high
fork %:high
zjmp %:gohere
sti r1, %1, :gohere

high: live %1
st r1, :gohere
zjmp %:high

