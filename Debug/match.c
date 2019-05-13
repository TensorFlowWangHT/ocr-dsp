




























//��һ�������ƥ��  
BOOL CTemplateMatching::TemplateMatch_NCC(BYTE *pTempDataBuf, BYTE *pTemplateBuf, int nTemplateHeight, int nTemplateWidth)  
{  
    int m,n;  
    double dSumST = 0;//�м�������(Sxy - S')*(Txy - T')֮��  
    double dSumS = 0; //�м�������(Sxy - S')ƽ����  
    double dSumT = 0; //�м�������(Txy - T')ƽ����  
  
    double dSPixelSum = 0;  
    double dTPixelSum = 0;  
  
    double dNCC = 0;//��һ�����Ʋ��  
      
    unsigned char tempDatapixel;//����ֵ  
    unsigned char templatepixel;  
  
    unsigned char AveraryDatapixel; //pTempDataBufƽ��ֵ  
    unsigned char AveraryTemplatepixel;//pTemplateBufƽ��ֵ  
  
    for (m=0; m<nTemplateHeight; m++)  
    {  
        for(n=0; n<nTemplateWidth; n++)  
        {  
            tempDatapixel = pTempDataBuf[TPos(m,n)];//ģ�������  
            templatepixel = pTemplateBuf[TPos(m,n)];//ģ������  
            dSPixelSum += tempDatapixel;  
            dTPixelSum += templatepixel;  
              
        }  
    }  
  
    AveraryDatapixel = (unsigned char)dSPixelSum/(nTemplateHeight*nTemplateWidth);  
    AveraryTemplatepixel = (unsigned char)dTPixelSum/(nTemplateHeight*nTemplateWidth);  
  
    for (m=0; m<nTemplateHeight; m++)  
    {  
        for(n=0; n<nTemplateWidth; n++)  
        {  
            tempDatapixel = pTempDataBuf[TPos(m,n)];//ģ�������  
            templatepixel = pTemplateBuf[TPos(m,n)];//ģ������  
            dSumS  += (double)(tempDatapixel - AveraryDatapixel)*(tempDatapixel - AveraryDatapixel);   
            dSumT  += (double)(templatepixel - AveraryTemplatepixel)*(templatepixel - AveraryTemplatepixel);  
            dSumST += (double)(tempDatapixel - AveraryDatapixel)*(templatepixel - AveraryTemplatepixel);  
        }  
    }  
      
    dNCC = dSumST/(sqrt(dSumS)*sqrt(dSumT));    ////��һ�����Ʋ�ȹ�ʽ  
    if (dNCC > 0.85)   //�����Բ�ȵ��ٽ�ֵ  
        return 1;  
    else  
        return 0;  
}  
  
//////////////////////////////////////////////////////////////////////////  
/* 
//Ԥ���жϡ���3*3ʮ�����ġ��������Ƿ����ƣ�������ƣ�����ƥ���жϡ��������Լ����жϴ����� 
//ǰ�᣺ģ�����9*9 
*/  
BOOL CTemplateMatching::Judgement(BYTE *pTempDataBuf, BYTE *pTemplateBuf, int nTemplateHeight, int nTemplateWidth)  
{  
    int m,n;  
    double dSum = 0;  
  
    int H = 0;//��߶��ֳ��ķ�,һ�ݵĸ߶�  
    int W = 0;//һ�ݵĿ��  
      
    H = nTemplateHeight/4;  
    W = nTemplateWidth/4;  
  
    //��һ��3*3���ϣ�  
    for (m=H-1;m<H+2;m++)  
    {  
        for (n=2*W-1;n<2*W+2;n++)  
        {  
            if (pTempDataBuf[TPos(m,n)] == pTemplateBuf[TPos(m,n)])  
                dSum++;  
        }  
    }  
  
    //�ڶ���3*3����  
    for (m=2*H-1;m<2*H+2;m++)  
    {  
        for (n=W-1;n<W+2;n++)  
        {  
            if (pTempDataBuf[TPos(m,n)] == pTemplateBuf[TPos(m,n)])  
                dSum++;  
        }  
    }  
  
    //������3*3���У�  
    for (m=2*H-1;m<2*H+2;m++)  
    {  
        for (n=2*W-1;n<2*W+2;n++)  
        {  
            if (pTempDataBuf[TPos(m,n)] == pTemplateBuf[TPos(m,n)])  
                dSum++;  
        }  
    }  
  
    //���ĸ�3*3���ң�  
    for (m=2*H-1;m<2*H+2;m++)  
    {  
        for (n=3*W-1;n<3*W+2;n++)  
        {  
            if (pTempDataBuf[TPos(m,n)] == pTemplateBuf[TPos(m,n)])  
                dSum++;  
        }  
    }  
  
    //�����3*3���£�  
    for (m=3*H-1;m<3*H+2;m++)  
    {  
        for (n=2*W-1;n<2*W+2;n++)  
        {  
            if (pTempDataBuf[TPos(m,n)] == pTemplateBuf[TPos(m,n)])  
                dSum++;  
        }  
    }  
  
    //�ж��������ﵽҪ�����ʾԤƥ��׼ȷ����֮��Ԥƥ��ʧ�ܣ������¸�ģ��ƥ��  
    if (dSum >= (5-1)*9)   //ȫ������3*3*5  
        return 1;  
    else  
        return 0;  
}  