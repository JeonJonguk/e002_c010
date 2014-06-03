//
//  CJPsdParser.h
//  SoundPhonics_Template
//
//  Created by j2enty on 13. 6. 11..
//
//

#ifndef __SoundPhonics_Template__CJPsdParser__
#define __SoundPhonics_Template__CJPsdParser__

#include "cocos2d.h"
#include "CJSprite.h"

#include "../../rapidjson/include/rapidjson/document.h"
#include "../../rapidjson/include/rapidjson/rapidjson.h"

using namespace cocos2d;

// PSD dataset.
struct PsdData
{
    std::string                                             key;
    std::string                                             name;
    std::string                                             file;
    
    cocos2d::CCPoint                                        pos;
    cocos2d::CCSize                                         size;
};




/**
 * @author          Lee.YJ
 * @brief           Psd parser class. (Used SaxParser)
 * @version         1.1
 * @date            2013.06.11
 * @since           2013.07.04
 */
class CJPsdParser : public cocos2d::CCSAXDelegator
{
    static rapidjson::Document initParse(const char *pageName);
    
    
private:
    /**
     * @brief       CCDictionary temp address variable.
     */
    cocos2d::CCDictionary                                   *_psdDatas;
    
    /**
     * @brief       PSDData struct variable.
     */
    PsdData                                                 *_data;
    
    
    
    
private:
    /**
     * @author      Lee.YJ
     * @brief       PsdData variable initialization.
     * @version     1.0
     * @param       void
     * @return      void
     * @exception
     * @date        2013.06.11
     * @since       2013.06.11
     */
    void _resetPsdData();

    /**
     * @author      Lee.YJ
     * @brief       PsdData(CCDictionary) address variable setting.
     * @version     1.0
     * @param       CCDictionary **pPsdDict - User using CCDictionary address pointer.
     * @return      void
     * @exception   If CCDictionary is not initializa, auto initialization within this function.
     * @date        2013.06.11
     * @since       2013.06.11
     */
    void _setPsdData(cocos2d::CCDictionary **pPsdDict);
    
    /**
     * @author      Lee.YJ
     * @brief       Util function for string compare.
     * @version     1.0
     * @param       std::string firstStr    -   Comparsion first string.
     *              std::string secondStr   -   Comparsion second string.
     * @return      bool                    -   YES : first & second string is same.
     *                                      -   NO  : first & second string is not same.
     * @exception
     * @date        2013.06.11
     * @since       2013.06.11
     */
    bool _isStringCompare(std::string firstStr, std::string secondStr);
    
    
    // CCSAXDelegator OVERIDING.
    void startElement(void *ctx, const char *name, const char **atts);
    void endElement(void *ctx, const char *name);
    void textHandler(void *ctx, const char *s, int len);
    
    
public:
    
    void setElement(rapidjson::Document document);
    
    
    
public:
    /**
     * @author      Lee.YJ
     * @brief       Psd data parsing.
     * @version     1.1
     * @param       std::string strPsdFileName   -   Parse target file name.
     *              CCDictionary **pPsdDict         -   Save dictionary address pointer at parsing result.
     * @return      void
     * @exception
     * @date        2013.06.11
     * @since       2013.07.04
     */
    
    
    static void parseToPsdJSON(std::string strPsdFileName,
                               cocos2d::CCDictionary **pPsdDict,
                               bool bIsCommonPath = false);
    
    static void parseToPsdXML(std::string strPsdFileName,
                              cocos2d::CCDictionary **pPsdDict,
                              bool bIsCommonPath = false);
    
    // CJPsdParser Creator & Destroyer.
    CJPsdParser();
    virtual ~CJPsdParser();
    
    
public:
    /**
     * @author      Lee.YJ
     * @brief       Get PsdData to CCDictionary object.
     * @version     1.1
     * @param       CCDictionary *pPsdDatas     - PsdData in CCDictionary
     * @return      PsdData*
     * @exception
     * @date        2013.06.11
     * @since       2013.07.04
     */
    static PsdData*     getPsdData(cocos2d::CCDictionary *pPsdDatas);
    
    /**
     * @author      Lee.YJ
     * @brief       Get Positioning sprite to CCDictionary.
     * @version     1.1
     * @param       std::string strResName      - Sprite resource tag name.
     *              CCDictionary *pPsdDatas     - PsdData in CCDictionary
     * @return      CJSprite*
     * @exception
     * @date        2013.06.11
     * @since       2013.07.04
     */
    static CJSprite*    getPsdSprite(std::string strResName, CCDictionary *pPsdDatas);
    
    /**
     * @author      JEON.JU
     * @brief       Get Positioning common sprite to CCDictionary.
     * @version     1.1
     * @param       std::string strResName      - Sprite resource tag name.
     *              CCDictionary *pPsdDatas     - PsdData in CCDictionary
     * @return      CJSprite*
     * @exception
     * @date        2013.06.11
     * @since       2013.07.04
     */
    static CJSprite*    getPsdCommonSprite(std::string strResName, CCDictionary *pPsdDatas);
    
    
    /**
     * @author      Lee.YJ
     * @brief       Get image position to CCDictionary.
     * @version     1.1
     * @param       std::string strResName      - Sprite resource tag name.
     *              CCDictionary *pPsdDatas     - PsdData in CCDictionary
     * @return      CCPoint
     * @exception
     * @date        2013.06.11
     * @since       2013.07.04
     */
    static CCPoint      getPsdPosition(std::string strResName, CCDictionary *pPsdDatas);
    
    /**
     * @author      Lee.YJ
     * @brief       Get image size to CCDictionary.
     * @version     1.1
     * @param       std::string strResName      - Sprite resource tag name.
     *              CCDictionary *pPsdDatas     - PsdData in CCDictionary
     * @return      CCSize
     * @exception
     * @date        2013.06.11
     * @since       2013.07.04
     */
    static CCSize       getPsdSize(std::string strResName, CCDictionary *pPsdData);
};





#endif /* defined(__SoundPhonics_Template__CJPsdParser__) */
