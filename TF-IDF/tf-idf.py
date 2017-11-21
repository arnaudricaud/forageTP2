import numpy as np

N = 30800

IDFS = [None] * N
IDFS[0] = "Ne pas prendre en compte"

with open("words.txt") as words:
	for lineWord in words:
		idWord = int(lineWord.split(" ")[0])
		word = lineWord.split(" ")[1]
		lastIdDoc = 1
		wordPresent = False
		nbDocsWithWord = 0
		with open("nsfabs_part1_out/docwords.txt") as docs:
			for lineDocs in docs:
				currentIdDoc = int(lineDocs.split(" ")[0])
				if lastIdDoc != currentIdDoc:
					if wordPresent:
						nbDocsWithWord += 1
					lastIdDoc = currentIdDoc
					wordPresent = False
				currentIdWord = int(lineDocs.split(" ")[1])
				if currentIdWord == idWord:
					wordPresent = True
		docs.close()
		if wordPresent:
			nbDocsWithWord += 1
		try:
			IDFS[idWord] = np.log((N-1) / nbDocsWithWord)
		except Exception as ex:
			IDFS[idWord] = 0
		print(IDFS[idWord])
words.close()

print(IDFS)
