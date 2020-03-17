#ifndef __SMS
#define __SMS

#include <string>
#include <sstream>
#include <list>
#include <iomanip>
#include <exception>
#include <vector>
#include <iostream>

class Media
{
public:
	Media(){};
	virtual ~Media(){}
	virtual std::string afficher() const = 0;
};

class Image : public Media
{
public:
	Image():Media(){};
	virtual ~Image(){};
	virtual std::string afficher() const {return "[[image]]";}
};
class Son : public Media
{
public:
	Son():Media(){};
	virtual ~Son(){};
	virtual std::string afficher() const {return "[[son]]";}
};
class Video : public Media
{
public:
	Video():Media(){};
	virtual ~Video(){};
	virtual std::string afficher() const {return "[[video]]";}
};

class MauvaisNumero : public std::invalid_argument
{
public:
	MauvaisNumero():std::invalid_argument(""){}
	virtual const char * what() const noexcept {return "mauvais numero";}
};

class Reseau;
class Telephone;

class Message
{
private:
	static int nb_messages;
	const int id;
protected:
	std::string _src, _dst;
	std::string _date;
public:
	Message(std::string src, std::string dst, std::string date):
		id(nb_messages), _src(src), _dst(dst), _date(date){nb_messages++;}
	virtual ~Message(){};
	virtual std::string afficher() const = 0;
	static int getCle() {return nb_messages;};
	std::string getDe() const {return _dst;}
	std::string getA() const {return _src;}
	void setDe(std::string de) {_src = de;}
	void setA(std::string a) {_dst = a;}
	int getId() const {return id;};
};

class SMS : public Message
{
private:
	std::string _texte;
public:
	SMS(std::string src, std::string dst, std::string date):Message(src, dst, date){}
	virtual ~SMS(){};
	void setTexte(std::string texte) {_texte = texte;}
	std::string getTexte() const {return _texte;}
	virtual std::string afficher() const {return getTexte();}
};

class MMS : public SMS
{
private:
	std::vector<Media *> _medias;
public:
	MMS(MMS * mms):MMS(_src, _dst, _date){
		for (auto &&m : mms->_medias)
		{
			_medias.push_back(m);
		}
		
	};
	MMS(std::string src, std::string dst, std::string date):SMS(src, dst, date){}
	void joindre(Media * m){_medias.push_back(m);}
	std::string afficher() const {
		std::ostringstream oss;
		oss << getTexte();
		for (auto &&m : _medias)
		{
			oss << m->afficher();
		}

		return oss.str();
	}
	virtual ~MMS() { for (auto &&m : _medias) delete m; }
};

class Reseau
{
private:
	std::list<Telephone*> _tels;
public:
	Reseau(){};
	~Reseau();
	std::string lister() const;
	void ajouter(std::string num);	
	Telephone& trouveTel(std::string num);

};

class Telephone
{
private:
	Reseau * _r;
	int _numero;
	std::vector<Message*> _messages;
public:
	Telephone(std::string num = "", Reseau * r = nullptr);
	~Telephone() { for (auto &&m : _messages) delete m; };
	void setNumero(std::string num) {
		if (num == "") _numero = 0;
		else _numero = std::stoi(num);
	}
	std::string getNumero() const {
		if (_numero == 0) return "";
		std::ostringstream oss;
		oss << std::setfill('0') << std::setw(10) << _numero;
		return oss.str();
	};
	Reseau* getReseau() const {return _r;}
	int getNbMessages() const {return _messages.size();}
	void recevoir(Message* msg) {_messages.push_back(msg);}
	void textoter(std::string num, std::string txt)
	{
		SMS * msg = new SMS(getNumero(), num, "date");
		SMS * m = new SMS(getNumero(), num, "date");
		msg->setTexte(txt);

		_messages.push_back(msg);
		try 
		{
			getReseau()->trouveTel(num).recevoir(m);
		} catch (std::exception&)
		{
			delete m;
			std::cout << "Pas trouvé : " << num << std::endl;
		}

	}

	void mmser(std::string dst, MMS * mms)
	{
		mms->setDe(getNumero());
		mms->setA(dst);
		MMS * m = new MMS(mms);
		_messages.push_back(mms);
		m->setDe(getNumero());
		m->setA(dst);

		try 
		{
			getReseau()->trouveTel(dst).recevoir(m);
		} catch(std::exception& e)
		{
			delete m;
		}
	}

	friend inline bool operator>(const Telephone& a, const Telephone& b){return a._numero > b._numero;};
};



#endif