file = open('dale.txt', 'r')

# Res
resRead = file.readline().rstrip().split(' ')
res = {
	'width': resRead[0],
	'height': resRead[1]
}

# Cameras
cameraRead = file.readline().rstrip().split(' ')
camera = {
	'x': cameraRead[0],
	'y': cameraRead[1],
	'z': cameraRead[2]
}
target = {
	'x': cameraRead[3],
	'y': cameraRead[4],
	'z': cameraRead[5]
}
up = {
	'x': cameraRead[6],
	'y': cameraRead[7],
	'z': cameraRead[8]
}
fov = cameraRead[9]
f = cameraRead[10]

# Materials
line = '='
materials = {}
while True:
	line = file.readline()
	if len(line) < 2:
		break

	materialLine = line.rstrip().split(' ')

	materials[materialLine[0]] = {
		'r': materialLine[1],
		'g': materialLine[2],
		'b': materialLine[3],
		'kd': materialLine[4],
		'ks': materialLine[5],
		'ke': materialLine[6],
		'alpha': materialLine[7]
	}

# Objects
line = '='
objs = []
while True:
	line = file.readline()
	if len(line) < 2:
		break
	
	line = file.readline()
	objLine = line.rstrip().split(' ')
	obj = {
		'type': objLine[0],
		'cx': objLine[1],
		'cy': objLine[2],
		'cz': objLine[3],
		'r': objLine[4],
		'material': objLine[5]
	}
	objs.append(obj)


print(materials)
print(objs)

