#include "TipUI.h"


//
const char* DEFAULT_TIP_FONT_NAME = "arial.ttf";



TipUI::TipUI(void):
	m_bg(nullptr),
	m_font_size(DEFAULT_TIP_FONT_SIZE),
	m_font_name(DEFAULT_TIP_FONT_NAME)
{
}


TipUI::~TipUI(void)
{
}



TipUI* TipUI::create( const std::string& _bg_file, const Rect& capInset, int maxWidth /*= 150*/)
{
	auto _tip_ui = TipUI::create();
	if(!_tip_ui->initFromFile(_bg_file,capInset,maxWidth))
	{
		return nullptr;
	}
	return _tip_ui;
}

bool TipUI::initFromFile( const std::string& _bg_file, const Rect& capInset, int maxWidth)
{
	m_bg = Scale9Sprite::create(capInset,_bg_file);
	if (!m_bg)
	{
		CCLOG("[TipUI::initFromFile] scale9sprite create failed");
		return false;
	}

	m_maxWidth = maxWidth;
	m_bg->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	this->addChild(m_bg);
	return true;
}



void TipUI::buildTipInfo()
{
	if (m_vec_tips.empty())
	{
		return;
	}


	Size orign = m_bg->getContentSize();
	Rect _capInset = static_cast<Scale9Sprite*>(m_bg)->getCapInsets();
	auto line_height = static_cast<Label*>(m_vec_tips.at(0))->getLineHeight();
	
	int nlines = calculateTipInfoLineCnt();

	// tip ui大小
	Size tip_ui_size;
	tip_ui_size.width = m_maxWidth;
	tip_ui_size.height = orign.height - _capInset.size.height + line_height * nlines;


	// 设置一下tip的大小
	this->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	this->setContentSize(tip_ui_size);
	// 设置到左上角
	m_bg->setPosition(Vec2(0,tip_ui_size.height));
	m_bg->setContentSize(tip_ui_size);

	// 实际内容偏移值
	float base_offset_y = (orign.height - _capInset.size.height)/2;
	float base_offset_x = _capInset.getMinX();

	int cnt = 0;
	for (auto _iter = m_vec_tips.begin(); _iter != m_vec_tips.end(); _iter++)
	{
		auto label = static_cast<Label*>(*_iter);
		label->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
		label->setPosition(Vec2(base_offset_x,tip_ui_size.height - base_offset_y - cnt * line_height));
		m_bg->addChild(label);
		cnt += std::count(label->getString().begin(),label->getString().end(),'\n') + 1;
	}


}



bool TipUI::genSKillTipInfo( int _sk_id, int _old_lv, int _new_lv )
{
	
	return true;
}

void TipUI::setTipFont( const std::string& font_file, int font_size )
{
	if (font_file.empty() || font_size <= 0)
	{
		return;
	}

	m_font_name = font_file;
	m_font_size = font_size;
}



int TipUI::calculateTipInfoLineCnt()
{
	int nRet = 0;
	if (m_vec_tips.empty())
	{
		return nRet;
	}

	for (auto _iter: m_vec_tips)
	{
		auto label = static_cast<Label*>(_iter);
		int nCount = std::count(label->getString().begin(),label->getString().end(),'\n');
		nRet += nCount + 1;
	}

	return nRet;
}




void TipUI::addLine( const std::string& text,const Color4B& color )
{
	TTFConfig ttfconf;
	ttfconf.fontFilePath = m_font_name;
	ttfconf.fontSize = m_font_size;
	auto label = Label::createWithTTF(ttfconf,text,TextHAlignment::LEFT,m_maxWidth);
	
	if(label)
	{
		label->setTextColor(color);
		m_vec_tips.pushBack(label);
	}
}




#ifdef _DEBUG

void TipUI::testTipUI()
{
	TTFConfig ttfconf;
	ttfconf.fontFilePath = m_font_name;
	ttfconf.fontSize = m_font_size;
	//auto label1 = Label::createWithTTF(ttfconf,"attack variables add 15",TextHAlignment::LEFT,m_maxWidth);
	//auto label2 = Label::createWithTTF(ttfconf,"defend variables add 234",TextHAlignment::LEFT,m_maxWidth);
	//auto label3 = Label::createWithTTF(ttfconf,"attack a line of enemy,attack \nmax five enemies,cost 12 mp,\nrest 10 second",TextHAlignment::LEFT,m_maxWidth);

	//m_vec_tips.pushBack(label1);
	//m_vec_tips.pushBack(label2);
	//m_vec_tips.pushBack(label3);

	addLine("attack variables add 15",Color4B::BLUE);
	addLine("defend variables add 234",Color4B::GREEN);
	addLine("attack a line of enemy,attack \nmax five enemies,cost 12 mp,\nrest 10 second",Color4B::RED);


	buildTipInfo();
}




#endif
