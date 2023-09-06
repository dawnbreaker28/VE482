#ifndef __PADCONF_H__
#define __PADCONF_H__

#define PADCONF_REGISTERS_BASE 0x48002030

#define PADCONF_MUXMODE(X)  (X & 0x7)	/* mode 1 til 7 [2:0] */
#define PADCONF_PULL_MODE(X)  ((X & 0x3) << 3)	/* 2 bits[4:3] */
#define PADCONF_PULL_MODE_PD_DIS PADCONF_PULL_MODE(0)	/* pull down disabled */
#define PADCONF_PULL_MODE_PD_EN PADCONF_PULL_MODE(1)	/* pull down enabled */
#define PADCONF_PULL_MODE_PU_DIS PADCONF_PULL_MODE(2)	/* pull up enabled */
#define PADCONF_PULL_MODE_PU_EN PADCONF_PULL_MODE(3)	/* pull up enabled */
#define PADCONF_INPUT_ENABLE(X)  ((X & 0x1) << 8)	/* 1 bits[8] */
#define PADCONF_OFF_MODE(X)  ((X & 0xFE) << 9)	/* 5 bits[13:9] */

/* padconf pin definitions */
#define CONTROL_PADCONF_SDRC_D0 (0x00000000)
#define CONTROL_PADCONF_SDRC_D2 (0x00000004)
#define CONTROL_PADCONF_SDRC_D4 (0x00000008)
#define CONTROL_PADCONF_SDRC_D6 (0x0000000C)
#define CONTROL_PADCONF_SDRC_D8 (0x00000010)
#define CONTROL_PADCONF_SDRC_D10 (0x00000014)
#define CONTROL_PADCONF_SDRC_D12 (0x00000018)
#define CONTROL_PADCONF_SDRC_D14 (0x0000001C)
#define CONTROL_PADCONF_SDRC_D16 (0x00000020)
#define CONTROL_PADCONF_SDRC_D18 (0x00000024)
#define CONTROL_PADCONF_SDRC_D20 (0x00000028)
#define CONTROL_PADCONF_SDRC_D22 (0x0000002C)
#define CONTROL_PADCONF_SDRC_D24 (0x00000030)
#define CONTROL_PADCONF_SDRC_D26 (0x00000034)
#define CONTROL_PADCONF_SDRC_D28 (0x00000038)
#define CONTROL_PADCONF_SDRC_D30 (0x0000003C)
#define CONTROL_PADCONF_SDRC_CLK (0x00000040)
#define CONTROL_PADCONF_SDRC_DQS1 (0x00000044)
#define CONTROL_PADCONF_SDRC_DQS3 (0x00000048)
#define CONTROL_PADCONF_GPMC_A2 (0x0000004C)
#define CONTROL_PADCONF_GPMC_A4 (0x00000050)
#define CONTROL_PADCONF_GPMC_A6 (0x00000054)
#define CONTROL_PADCONF_GPMC_A8 (0x00000058)
#define CONTROL_PADCONF_GPMC_A10 (0x0000005C)
#define CONTROL_PADCONF_GPMC_D1 (0x00000060)
#define CONTROL_PADCONF_GPMC_D3 (0x00000064)
#define CONTROL_PADCONF_GPMC_D5 (0x00000068)
#define CONTROL_PADCONF_GPMC_D7 (0x0000006C)
#define CONTROL_PADCONF_GPMC_D9 (0x00000070)
#define CONTROL_PADCONF_GPMC_D11 (0x00000074)
#define CONTROL_PADCONF_GPMC_D13 (0x00000078)
#define CONTROL_PADCONF_GPMC_D15 (0x0000007C)
#define CONTROL_PADCONF_GPMC_NCS1 (0x00000080)
#define CONTROL_PADCONF_GPMC_NCS3 (0x00000084)
#define CONTROL_PADCONF_GPMC_NCS5 (0x00000088)
#define CONTROL_PADCONF_GPMC_NCS7 (0x0000008C)
#define CONTROL_PADCONF_GPMC_NADV_ALE (0x00000090)
#define CONTROL_PADCONF_GPMC_NWE (0x00000094)
#define CONTROL_PADCONF_GPMC_NBE1 (0x00000098)
#define CONTROL_PADCONF_GPMC_WAIT0 (0x0000009C)
#define CONTROL_PADCONF_GPMC_WAIT2 (0x000000A0)
#define CONTROL_PADCONF_DSS_PCLK (0x000000A4)
#define CONTROL_PADCONF_DSS_VSYNC (0x000000A8)
#define CONTROL_PADCONF_DSS_DATA0 (0x000000AC)
#define CONTROL_PADCONF_DSS_DATA2 (0x000000B0)
#define CONTROL_PADCONF_DSS_DATA4 (0x000000B4)
#define CONTROL_PADCONF_DSS_DATA6 (0x000000B8)
#define CONTROL_PADCONF_DSS_DATA8 (0x000000BC)
#define CONTROL_PADCONF_DSS_DATA10 (0x000000C0)
#define CONTROL_PADCONF_DSS_DATA12 (0x000000C4)
#define CONTROL_PADCONF_DSS_DATA14 (0x000000C8)
#define CONTROL_PADCONF_DSS_DATA16 (0x000000CC)
#define CONTROL_PADCONF_DSS_DATA18 (0x000000D0)
#define CONTROL_PADCONF_DSS_DATA20 (0x000000D4)
#define CONTROL_PADCONF_DSS_DATA22 (0x000000D8)
#define CONTROL_PADCONF_CAM_HS (0x000000DC)
#define CONTROL_PADCONF_CAM_XCLKA (0x000000E0)
#define CONTROL_PADCONF_CAM_FLD (0x000000E4)
#define CONTROL_PADCONF_CAM_D1 (0x000000E8)
#define CONTROL_PADCONF_CAM_D3 (0x000000EC)
#define CONTROL_PADCONF_CAM_D5 (0x000000F0)
#define CONTROL_PADCONF_CAM_D7 (0x000000F4)
#define CONTROL_PADCONF_CAM_D9 (0x000000F8)
#define CONTROL_PADCONF_CAM_D11 (0x000000FC)
#define CONTROL_PADCONF_CAM_WEN (0x00000100)
#define CONTROL_PADCONF_CSI2_DX0 (0x00000104)
#define CONTROL_PADCONF_CSI2_DX1 (0x00000108)
#define CONTROL_PADCONF_MCBSP2_FSX (0x0000010C)
#define CONTROL_PADCONF_MCBSP2_DR (0x00000110)
#define CONTROL_PADCONF_MMC1_CLK (0x00000114)
#define CONTROL_PADCONF_MMC1_DAT0 (0x00000118)
#define CONTROL_PADCONF_MMC1_DAT2 (0x0000011C)
#define CONTROL_PADCONF_MMC2_CLK (0x00000128)
#define CONTROL_PADCONF_MMC2_DAT0 (0x0000012C)
#define CONTROL_PADCONF_MMC2_DAT2 (0x00000130)
#define CONTROL_PADCONF_MMC2_DAT4 (0x00000134)
#define CONTROL_PADCONF_MMC2_DAT6 (0x00000138)
#define CONTROL_PADCONF_MCBSP3_DX (0x0000013C)
#define CONTROL_PADCONF_MCBSP3_CLKX (0x00000140)
#define CONTROL_PADCONF_UART2_CTS (0x00000144)
#define CONTROL_PADCONF_UART2_TX (0x00000148)
#define CONTROL_PADCONF_UART1_TX (0x0000014C)
#define CONTROL_PADCONF_UART1_CTS (0x00000150)
#define CONTROL_PADCONF_MCBSP4_CLKX (0x00000154)
#define CONTROL_PADCONF_MCBSP4_DX (0x00000158)
#define CONTROL_PADCONF_MCBSP1_CLKR (0x0000015C)
#define CONTROL_PADCONF_MCBSP1_DX (0x00000160)
#define CONTROL_PADCONF_MCBSP_CLKS (0x00000164)
#define CONTROL_PADCONF_MCBSP1_CLKX (0x00000168)
#define CONTROL_PADCONF_UART3_RTS_SD (0x0000016C)
#define CONTROL_PADCONF_UART3_TX_IRTX (0x00000170)
#define CONTROL_PADCONF_HSUSB0_STP (0x00000174)
#define CONTROL_PADCONF_HSUSB0_NXT (0x00000178)
#define CONTROL_PADCONF_HSUSB0_DATA1 (0x0000017C)
#define CONTROL_PADCONF_HSUSB0_DATA3 (0x00000180)
#define CONTROL_PADCONF_HSUSB0_DATA5 (0x00000184)
#define CONTROL_PADCONF_HSUSB0_DATA7 (0x00000188)
#define CONTROL_PADCONF_I2C1_SDA (0x0000018C)
#define CONTROL_PADCONF_I2C2_SDA (0x00000190)
#define CONTROL_PADCONF_I2C3_SDA (0x00000194)
#define CONTROL_PADCONF_MCSPI1_CLK (0x00000198)
#define CONTROL_PADCONF_MCSPI1_SOMI (0x0000019C)
#define CONTROL_PADCONF_MCSPI1_CS1 (0x000001A0)
#define CONTROL_PADCONF_MCSPI1_CS3 (0x000001A4)
#define CONTROL_PADCONF_MCSPI2_SIMO (0x000001A8)
#define CONTROL_PADCONF_MCSPI2_CS0 (0x000001AC)
#define CONTROL_PADCONF_SYS_NIRQ (0x000001B0)
#define CONTROL_PADCONF_SAD2D_MCAD0 (0x000001B4)
#define CONTROL_PADCONF_SAD2D_MCAD2 (0x000001B8)
#define CONTROL_PADCONF_SAD2D_MCAD4 (0x000001BC)
#define CONTROL_PADCONF_SAD2D_MCAD6 (0x000001C0)
#define CONTROL_PADCONF_SAD2D_MCAD8 (0x000001C4)
#define CONTROL_PADCONF_SAD2D_MCAD10 (0x000001C8)
#define CONTROL_PADCONF_SAD2D_MCAD12 (0x000001CC)
#define CONTROL_PADCONF_SAD2D_MCAD14 (0x000001D0)
#define CONTROL_PADCONF_SAD2D_MCAD16 (0x000001D4)
#define CONTROL_PADCONF_SAD2D_MCAD18 (0x000001D8)
#define CONTROL_PADCONF_SAD2D_MCAD20 (0x000001DC)
#define CONTROL_PADCONF_SAD2D_MCAD22 (0x000001E0)
#define CONTROL_PADCONF_SAD2D_MCAD24 (0x000001E4)
#define CONTROL_PADCONF_SAD2D_MCAD26 (0x000001E8)
#define CONTROL_PADCONF_SAD2D_MCAD28 (0x000001EC)
#define CONTROL_PADCONF_SAD2D_MCAD30 (0x000001F0)
#define CONTROL_PADCONF_SAD2D_MCAD32 (0x000001F4)
#define CONTROL_PADCONF_SAD2D_MCAD34 (0x000001F8)
#define CONTROL_PADCONF_SAD2D_MCAD36 (0x000001FC)
#define CONTROL_PADCONF_SAD2D_NRESPWRON (0x00000200)
#define CONTROL_PADCONF_SAD2D_ARMNIRQ (0x00000204)
#define CONTROL_PADCONF_SAD2D_SPINT (0x00000208)
#define CONTROL_PADCONF_SAD2D_DMAREQ0 (0x0000020C)
#define CONTROL_PADCONF_SAD2D_DMAREQ2 (0x00000210)
#define CONTROL_PADCONF_SAD2D_NTRST (0x00000214)
#define CONTROL_PADCONF_SAD2D_TDO (0x00000218)
#define CONTROL_PADCONF_SAD2D_TCK (0x0000021C)
#define CONTROL_PADCONF_SAD2D_MSTDBY (0x00000220)
#define CONTROL_PADCONF_SAD2D_IDLEACK (0x00000224)
#define CONTROL_PADCONF_SAD2D_SWRITE (0x00000228)
#define CONTROL_PADCONF_SAD2D_SREAD (0x0000022C)
#define CONTROL_PADCONF_SAD2D_SBUSFLAG (0x00000230)
#define CONTROL_PADCONF_SDRC_CKE1 (0x00000234)
#define CONTROL_PADCONF_SDRC_BA0 (0x00000570)
#define CONTROL_PADCONF_SDRC_A0 (0x00000574)
#define CONTROL_PADCONF_SDRC_A2 (0x00000578)
#define CONTROL_PADCONF_SDRC_A4 (0x0000057C)
#define CONTROL_PADCONF_SDRC_A6 (0x00000580)
#define CONTROL_PADCONF_SDRC_A8 (0x00000584)
#define CONTROL_PADCONF_SDRC_A10 (0x00000588)
#define CONTROL_PADCONF_SDRC_A12 (0x0000058C)
#define CONTROL_PADCONF_SDRC_A14 (0x00000590)
#define CONTROL_PADCONF_SDRC_NCS1 (0x00000594)
#define CONTROL_PADCONF_SDRC_NRAS (0x00000598)
#define CONTROL_PADCONF_SDRC_NWE (0x0000059C)
#define CONTROL_PADCONF_SDRC_DM1 (0x000005A0)
#define CONTROL_PADCONF_SDRC_DM3 (0x000005A4)
#define CONTROL_PADCONF_ETK_CLK (0x000005A8)
#define CONTROL_PADCONF_ETK_D0 (0x000005AC)
#define CONTROL_PADCONF_ETK_D2 (0x000005B0)
#define CONTROL_PADCONF_ETK_D4 (0x000005B4)
#define CONTROL_PADCONF_ETK_D6 (0x000005B8)
#define CONTROL_PADCONF_ETK_D8 (0x000005BC)
#define CONTROL_PADCONF_ETK_D10 (0x000005C0)
#define CONTROL_PADCONF_ETK_D12 (0x000005C4)
#define CONTROL_PADCONF_ETK_D14 (0x000005C8)

int padconf_init();
int padconf_set(u32_t padconf, u32_t mask, u32_t value);
int padconf_release();

#endif /* __PADCONF_H__ */
