#include"mpu6050.h"
//#include"I2C.h"
#include "delay.h" 
#include "IIC.h"
#include "usart.h"
#include "math.h" 
//#include "led.h"    						    						

//����MPU6050�ڲ���ַ
/****************************************/
#define  SELF_TEST_X    0x0D              //X���Բ⣬�������ٶȼ��������ǣ���ע��Ĵ���λ�ֲ���������ֱ�Ϊ0~4λ��FTΪ��������ֵ���Բ���������ѡ������Ϊ+-250��/s;
#define  SELF_TEST_Y    0x0E              //Y���Բ⣬�������ٶȼ��������ǣ�131Ϊ250��/s���̵ķֱ��ʣ�65536/500=131, ��Ϊ16λ�ֱ��ʣ�
#define  SELF_TEST_Z    0x0F              //Z���Բ⣬�������ٶȼ��������ǣ�
#define  SELF_TEST_A    0x10              //X���Բ⣬���ٶȼƵ�ÿ����ĵ��ֽ�
														//����Բ�ʹ��-�Բⲻʹ��
														//�Բ��Ŀ���ǲ��������Ǻͼ��ٶȼƵ�����������е�͵������Բ����ֵ�ı仯�ٷֱ��Ƿ�����Чֵ֮�ڣ���ֵ����ͨ��MotionApps������
														//������ͨ��FT��ֵ���в�����FT��ֵ�����Բ�Ĵ�����ֵ�����ģ���ο������ֲ�
#define	SMPLRT_DIV		0x19					//������Ƶ��sample,�����������ʣ�����ֵ��0x07(125Hz)��������ʷ�Ƶ�õ��������ʡ�
														//�������Ĵ��������DMP��FIFO������˶���ⶼ�Բ�������Ϊ������������ʵ�DLPF�����ֵ�ͨ�˲�����ʹ��ʱΪ1kHz����ֹʱΪ8KHz
														//ÿ���ᶼ���Ե������ã�sample=�������������/(1+SMPLRT_DIV);

#define	CONFIG			0x1A					//��ʹ��FSYNC(�ⲿԤ����ͬ���ź�)��DLPF_CFG[2~0],�����������Ƿ�ͨ��DLPF������ֵ��0x06(5Hz)��ͨ�˲�������5Hz��
														//�Լ��ٶȺ������Ƕ���Ч�����Ƶ��Ϊ1kHz������SMPLRT_DIV��Ƶ�ʻ�׼

#define	GYRO_CONFIG		0x1B					//���������üĴ������������Լ켰���̣����Ե���ʹ���������Լ�[7~5]��FS_SEL[4~3],00+-250��01+��500��10+-1000��11+-2000
														//����ֵ��0x18(���Լ죬�������2000deg/s)
#define	ACCEL_CONFIG	0x1C					//���ٶȼ����üĴ������Լ켰���̣����Ե���ʹ���������Լ죻DHPF���ָ�ͨ�˲�Ƶ�ʣ�����ֵ��0x0c(���Լ죬16G��5Hz)

#define  MOT_THR        0x1F 					//�˶���ֵⷧ���ٶ�mg��������ֵ�����жϣ��жϼĴ������Լ����ĸ��ᳬ����ֵ���ͼ��ԡ�

#define  FIFO_EN			0x23					//�¶ȴ�����FIFOʹ�ܣ������Ǹ�����FIFO����ʹ�ܣ��������ݼĴ��������ݶ����Ի�����FIFO�������ǿ���ʹ�ܸ������Ƿ񻺳���FIFO��
														//���ٶȼ�����ֻ��ѡ���Ƿ�������ͬʱ������FIFO��
#define  I2C_MST_CTRL   0x24					//���Ƹ�������Ϊ��IIC�����ã������IIC��һ������ʱ���ܲã�����ͬ���������������ݣ�dataready�жϣ���ͬ����ȷ���ж����ⲿ��
														//������������д���ⲿ���ݼĴ���֮�󴥷�,������IICƵ��

#define  I2C_SLV0_ADDR	0x25					//����������������Ķ�д�źţ��ʹ�������ַ��7λ��
#define  I2C_SLV0_REG	0x26					//��ַ��ָʾ�ڲ��Ĵ����ĵ�ַ���ѸüĴ���������д������������ߴ�����д��üĴ�����
#define  I2C_SLV0_CTRL	0x27					//�Ƿ����ݸߵ��ֽڽ���������������ο������ֲ�
#define  I2C_SLV1_ADDR	0x28					//����������������Ķ�д�źţ��ʹ�������ַ��7λ��
#define  I2C_SLV1_REG	0x29					//��ַ��ָʾ�ڲ��Ĵ����ĵ�ַ���ѸüĴ���������д������������ߴ�����д��üĴ�����
#define  I2C_SLV1_CTRL	0x2a					//�Ƿ����ݸߵ��ֽڽ���������������ο������ֲ�
#define  I2C_SLV2_ADDR	0x2b					//����������������Ķ�д�źţ��ʹ�������ַ��7λ��
#define  I2C_SLV2_REG	0x2c					//��ַ��ָʾ�ڲ��Ĵ����ĵ�ַ���ѸüĴ���������д������������ߴ�����д��üĴ�����
#define  I2C_SLV2_CTRL	0x2d					//�Ƿ����ݸߵ��ֽڽ���������������ο������ֲ�
#define  I2C_SLV3_ADDR	0x2e					//����������������Ķ�д�źţ��ʹ�������ַ��7λ��
#define  I2C_SLV3_REG	0x2f					//��ַ��ָʾ�ڲ��Ĵ����ĵ�ַ���ѸüĴ���������д������������ߴ�����д��üĴ�����
#define  I2C_SLV3_CTRL	0x30					//�Ƿ����ݸߵ��ֽڽ���������������ο������ֲ�
#define  I2C_SLV4_ADDR	0x31					//����������������Ķ�д�źţ��ʹ�������ַ��7λ��
#define  I2C_SLV4_REG	0x32					//��ַ��ָʾ�ڲ��Ĵ����ĵ�ַ���ѸüĴ���������д������������ߴ�����д��üĴ�����
#define  I2C_SLV4_DO 	0x33
#define  I2C_SLV4_CTRL	0x34					//�Ƿ����ݸߵ��ֽڽ���������������ο������ֲ�  
#define  I2C_SLV4_DI 	0x35

#define  I2_MST_STATUS	0x36					//IIC״̬�Ĵ�����ֻ����������0~4�жϡ�����

#define  INT_PIN_CFG    0x37              //INT�����жϵ�ƽ��0����Ч��1Ϊ�͵�ƽ��Ч�����������죬��Ե������50us�����壩���ߵ�ƽ������ֱ���ж��������ֻ�ж��üĴ����Ƿ����жϡ�����
#define  INT_ENABLE     0x38              //�˶����ʹ�ܣ�FIFO����Ƿ�����жϣ�DATA_ready�ж�ʹ�ܡ�����(�����������ݼĴ��������)
#define  INT_STATUS     0x3A              //��Ӧ������ж�Դ��ֻ��

														
														//�����������õĲ������ʸ������ݼĴ�����ֵ
#define	ACCEL_XOUT_H	0x3B					//���ٶ����ݼĴ��������ֽ�
#define	ACCEL_XOUT_L	0x3C					//�Բ�������д�����ݼĴ���
#define	ACCEL_YOUT_H	0x3D					//16λ�����Ʋ�����ʽ�洢
#define	ACCEL_YOUT_L	0x3E
#define	ACCEL_ZOUT_H	0x3F
#define	ACCEL_ZOUT_L	0x40

#define	TEMP_OUT_H		0x41				   //�¶ȴ��������ݼĴ������Բ�������д�����ݣ����������ݼĴ������ⲿ���������ݼĴ���
#define	TEMP_OUT_L		0x42				   //������ּĴ������ڲ��Ĵ������û��ɶ��Ĵ��������߽ӿڿ���ʱ���������ݼĴ������ݸ��µ��ɶ��Ĵ�����
														//�ڲ���ͻ����ȡ�Ĵ�������ֵʱ��ʵ���϶����ǿɶ��Ĵ�����ֵ���Ա�֤����������ͬһ����ʱ�̵ĸߵ��ֽڵ�
														//���ݣ�����ߵ������ֽڲ���Ӧ

#define	GYRO_XOUT_H		0x43					//���������ݼĴ����������ֽڣ�
#define	GYRO_XOUT_L		0x44	
#define	GYRO_YOUT_H		0x45
#define	GYRO_YOUT_L		0x46
#define	GYRO_ZOUT_H		0x47
#define	GYRO_ZOUT_L		0x48
														//�Ĵ���0x49~0x60Ϊ�ⲿ�Ӵ�����0~3�����ݼĴ�����ֻ��
#define  I2C_SLV0_DO    0x63     			//����д�������0������
#define  I2C_SLV1_DO    0x64     			//����д�������1������
#define  I2C_SLV2_DO    0x65     			//����д�������2������
#define  I2C_SLV3_DO    0x66     			//����д�������3������

#define  I2C_MST_DELAY_CTRL  0x67         //�ⲿ�������������Ρ�����
#define  SIGNAL_PATH_RESET   0x68         //�����ǣ����ٶȣ��¶ȴ�������λ
#define  MOT_DETECT_CTRL     0x69			//���ٶȼ��ϵ���ʱʱ��
#define  USER_CTRL           0x7a			//FIFOʹ�ܣ�IIC��ʹ�ܣ�IIC�ӿ�ѡ��FIFO��λ��IIC����λ����λ�����Ĵ���

#define	PWR_MGMT_1		0x6B					//��Դ����1��ʱ��Դ��װ�ø�λ���¶ȴ�����ʹ��0������ֵ��0x00(��������)
#define	PWR_MGMT_2		0x6C	  				//��Դ����2���������Ƿ��ڴ���ģʽ
#define  FIFO_COUNT_H   0x72					//FIFOָ����ֽڣ�ֻ�����ȷ��ʸ��ֽڣ�����ֽ�
#define  FIFO_COUNT_L   0x73					//FIFOָ����ֽڣ�ֻ��
#define  FIFO_R_W       0x74					//��дFIFO����Ĵ���
#define	WHO_AM_I			0x75					//IIC��ַ�Ĵ���(Ĭ����ֵ0x68��ֻ��)������ID
#define	SlaveAddress	0xD0					//IICд��ʱ�ĵ�ַ�ֽ����ݣ�+1Ϊ��ȡ
/**************************************/
//���Ư���벹��//
#define  ACC_Y_offset   0															//���ٶȼ�Y������ƫ�ƣ��ɱ궨
#define  ACC_Z_offset	0														   //���ٶȼ�Z������ƫ��
#define  GRY_X_offset	0														//�����ǵ����Ư��
#define  dt       0.005																//����ʱ�䳣��
//****************************************
//�������ͼ�����
//****************************************
s16  temp_acc_y=0,temp_acc_z=0;				   	//��������м����������������Ϊ���ε�
float temp_Gry_x=0;
float  Acc_angle=0;															//���ٶȵ���Ǽ���ó��Ľ��Ϊ�������ͣ�
float  angle=0;																	//�˲���ĽǶ�

//****************************************
//��������
//****************************************
//MPU6050��������
void  InitMPU6050(void);																			//��ʼ��MPU6050
void  Read_Acc(void);																				//��ȡACCֵ
void  Read_Gry(void);																				//��ȡGryֵ
void  count_Acc_angle(void);																		//������ٶ���ǣ���λ���ȣ�
u8 Single_ReadIIC(u8 REG_Address);																//��ȡI2C����һ���ֽ�
void  Single_WriteIIC(u8 REG_Address,u8 REG_data);	                           	//��I2Cд��һ���ֽ�����
//**************************************
//��6050д��һ���ֽ�����
//**************************************
void Single_WriteIIC(u8 REG_Address,u8 REG_data)
{
    IIC_Start();                  //��ʼ�ź�
    IIC_SendByte(SlaveAddress+0);   //�����豸��ַ+0д�ź�
	 IIC_Wait_Ack();
    IIC_SendByte(REG_Address);    //�ڲ��Ĵ�����ַ��
	 IIC_Wait_Ack();
    IIC_SendByte(REG_data);       //�ڲ��Ĵ�������
	 IIC_Wait_Ack();
    IIC_Stop();                   //����ֹͣ�ź�  
}
//**************************************
//��mpu6050��ȡһ���ֽ�����
//**************************************
u8 Single_ReadIIC(u8 REG_Address)
{
	u8 REG_data=0;
	IIC_Start();                   //��ʼ�ź�
	IIC_SendByte(SlaveAddress);    //�����豸��ַ+д�ź�
	IIC_Wait_Ack();
	IIC_SendByte(REG_Address);     //���ʹ洢��Ԫ��ַ����0��ʼ
	IIC_Wait_Ack();	
	IIC_Start();                   //��ʼ�ź�
	IIC_SendByte(SlaveAddress+1);  //�����豸��ַ+���ź�
	IIC_Wait_Ack();
	REG_data=IIC_ReadByte(0);       //�����Ĵ�������
	IIC_Wait_Ack();
	IIC_SendAck();                  //����Ӧ���ź�
	IIC_Stop();                     //ֹͣ�ź�
	return REG_data;
}

//**************************************
//��ʼ��MPU6050
//**************************************
void InitMPU6050()
{
	IIC_Init(); 																	//IIC��ʼ��
	Single_WriteIIC(PWR_MGMT_1, 0x00);										//��Դ����1���������״̬��ʱ��Ϊ�ڲ�8MHz
	Single_WriteIIC(SMPLRT_DIV, 0x04);										//��������125Hz
	Single_WriteIIC(CONFIG, 0x06);											//��ʹ��FSYNC,��ʹ����ͬ���������ʣ�DLPF_CFG[2~0],�����������Ƿ�ͨ��DLPF��
																						//����ֵ��0x06(5Hz)��ͨ�˲�������5Hz��
																						//�Լ��ٶȺ������Ƕ���Ч�����Ƶ��Ϊ1kHz������SMPLRT_DIV��Ƶ�ʻ�׼
	Single_WriteIIC(GYRO_CONFIG, 0x10);										//���Բ⣬+-1000��/s
	Single_WriteIIC(ACCEL_CONFIG, 0x08);									//���Բ⣬+-4g
}
u8 GetData1(u8 REG_Address)										   //����ֵΪ�з��ŵ����Σ�16λ
{
	u8 H=0;
	H = Single_ReadIIC(REG_Address);											//�ȶ����ֽڣ��ٶ����ֽ�
	return H;   															//�ϳ����ݣ�Ϊ�з���������
}
//**************************************
//��ȡmpu6050�ڲ����ݣ������ֽڣ��ϳ�����
//**************************************
s16 GetData(u8 REG_Address)										//����ֵΪ�з��ŵ����Σ�16λ
{
	s16 H=0,L=0;
	H = Single_ReadIIC(REG_Address);											//�ȶ����ֽڣ��ٶ����ֽ�
	L = Single_ReadIIC(REG_Address+1);
	return (H<<8)+L;   															//�ϳ����ݣ�Ϊ�з���������
}
//���ٶȼ�Y��Z���ԭʼ����
void Read_Acc()
{
	temp_acc_y = GetData(ACCEL_YOUT_H) + ACC_Y_offset;				//�õ����ٶ�X�����ݣ�16λ�Ķ����������룩��
	temp_acc_z = GetData(ACCEL_ZOUT_H) + ACC_Z_offset;				//�õ����ٶ�X�����ݣ�16λ�Ķ����Ʋ��룩��
	printf("%d", GetData(temp_acc_y));									//���Դ���
	printf("	");
}																					//����������Ϊ���ε�		
//�����м������ֵ
void count_Acc_angle()												    	//�������
{
	Read_Acc();
  	if(temp_acc_y>0)
	{
		Acc_angle = atan2((float)temp_acc_y,(float)temp_acc_z)*(180/3.14159265);		  //�����м���

	}
		else
		{
	   Acc_angle = atan2((float)temp_acc_z,(float)temp_acc_y)*(180/3.14159265)-90;		//�����м���
		Acc_angle = -Acc_angle;

		}
}
//�����Ǽ���X��Y��Ľ��ٶ�
void Read_Gry_x()
{
  	temp_Gry_x = GetData(GYRO_XOUT_H) ;									//��ȡ������X�����ݼĴ������õ����������ݣ�16λ�Ķ����Ʋ��룩��
	temp_Gry_x = temp_Gry_x*(0.030517);
}

void Balance_filter()
{
   count_Acc_angle();																			 //������ٶȼƵ����ֵ
   Read_Gry_x();																					 //��ȡ�����ǵ�ֵ
	angle=(0.9)*(angle+temp_Gry_x*dt) + (0.1)*Acc_angle;							 //�����˲�	
																					 //PID����PWMֵ
} 
