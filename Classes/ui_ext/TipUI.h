#pragma once
#include "../data/GameData.h"
#include "extensions/cocos-ext.h"


USING_NS_CC_EXT;


/*
 * Tip 相关
 */


class TipUI : public Node
{
public:
	TipUI(void);
	~TipUI(void);


	enum
	{
		DEFAULT_TIP_FONT_SIZE = 16,
	};



	static TipUI* create(const std::string& _bg_file, const Rect& capInset,int maxWidth = 150);



	/*
	 * @desc 设置tip显示的字体以及字号
	 * @param font_file 字体路径
	 * @param font_size 字体大小
	 * @return
	 *	
	 */
	void setTipFont(const std::string& font_file, int font_size);


	/*
	 * @desc 生成技能tip信息
	 * @param _sk_id 技能id
	 * @param _old_lv 老技能等级
	 * @param _new_lv 新技能等级
	 * @return
	 *	
	 */
	bool genSKillTipInfo(int _sk_id, int _old_lv, int _new_lv);



#ifdef _DEBUG

	void testTipUI();

#endif



	CREATE_FUNC(TipUI);

protected:

	//
	bool initFromFile(const std::string& _bg_file, const Rect& capInset, int maxWidth);


	// 排版tip信息
	void buildTipInfo();


	// 计算tip信息行数
	int calculateTipInfoLineCnt();


	//
	void addLine(const std::string& text,const Color4B& color);


private:

	// Scale9Sprite
	Node* m_bg;
	// Tips
	Vector<Node*> m_vec_tips;
	// 内容最大长度
	int m_maxWidth;


	std::string m_font_name;
	int m_font_size;

};

