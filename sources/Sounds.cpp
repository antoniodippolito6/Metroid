#include <QDir>
#include "Sounds.h"

using namespace MT;

Sounds* Sounds::instance()
{
	static Sounds uniqueInstance;
	return &uniqueInstance;
}

Sounds::Sounds()
{
	QStringList sound_files = QDir("Sounds/").entryList(QStringList() << "*.wav", QDir::Files);
	for (auto& f : sound_files)
	{
		std::string name = QFileInfo(f).baseName().toStdString();
		_sounds[name] = new QSoundEffect();
		_sounds[name]->setSource(QUrl::fromLocalFile(QString("Sounds/") + f));
	}

	QStringList music_files = QDir("soundtrack/").entryList(QStringList() << "*.wav", QDir::Files);
	for (auto& f : music_files)
	{
		std::string name = QFileInfo(f).baseName().toStdString();
		_musics[name] = new QSoundEffect();
		_musics[name]->setSource(QUrl::fromLocalFile(QString("soundtrack/") + f));
	}
}

void Sounds::playSound(const std::string& id)
{
	if (_sounds.find(id) != _sounds.end())
		_sounds[id]->play();
}

void Sounds::playMusic(const std::string& id, bool loop)
{
	if (_musics.find(id) != _musics.end())
	{
		if (loop)
			_musics[id]->setLoopCount(QSoundEffect::Infinite);

		_musics[id]->play();
	}
}

void Sounds::stopMusic(const std::string& id)
{
	if (_musics.find(id) != _musics.end())
		_musics[id]->stop();
}