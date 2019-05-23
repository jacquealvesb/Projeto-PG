def readFile(path):
	file = open(path, 'r')

	# Res
	resRead = file.readline().rstrip().split(' ')
	res = {
		'width': int(resRead[0]),
		'height': int(resRead[1])
	}

	# Cameras
	cameraRead = file.readline().rstrip().split(' ')
	camera = {
		'x': float(cameraRead[0]),
		'y': float(cameraRead[1]),
		'z': float(cameraRead[2])
	}
	target = {
		'x': float(cameraRead[3]),
		'y': float(cameraRead[4]),
		'z': float(cameraRead[5])
	}
	up = {
		'x': float(cameraRead[6]),
		'y': float(cameraRead[7]),
		'z': float(cameraRead[8])
	}
	fov = float(cameraRead[9])
	f = float(cameraRead[10])

	# Materials
	line = '='
	materials = {}
	while True:
		line = file.readline()
		if len(line) < 2:
			break

		materialLine = line.rstrip().split(' ')

		materials[materialLine[0]] = {
			'r': float(materialLine[1]),
			'g': float(materialLine[2]),
			'b': float(materialLine[3]),
			'kd': float(materialLine[4]),
			'ks': float(materialLine[5]),
			'ke': float(materialLine[6]),
			'alpha': float(materialLine[7])
		}

	# Objects
	line = '='
	objs = []
	while True:
		line = file.readline()

		if len(line) < 2:
			break
		
		objLine = line.rstrip().split(' ')
		obj = {
			'type': objLine[0],
			'cx': float(objLine[1]),
			'cy': float(objLine[2]),
			'cz': float(objLine[3]),
			'r': float(objLine[4]),
			'material': objLine[5]
		}
		
		objs.append(obj)

	return (res, camera, target, up, fov, f, materials, objs)