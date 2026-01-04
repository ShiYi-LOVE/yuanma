#include "Android_draw/draw.h"


#if defined(USE_OPENGL)
    #include "imgui_image.h"
#else
    #include "VulkanUtils.h"
#endif

#include "picture_ZhenAiKun_png.h"




static bool fxk1 = 0;//复选框
static bool fxk2 = 0;//复选框
static bool fxk3 = 0;//复选框
int panding1 = 0;//判定
int panding2 = 0;//判定
int panding3 = 0;//判定
bool main_thread_flag = true;

int abs_ScreenX = 0;
int abs_ScreenY = 0;



/**
 * imgui测试
 */
#if defined(USE_OPENGL)
    TextureInfo op_img;
#else
    MyTextureData vk_img;
#endif

int main(int argc, char *argv[]) {
    //获取屏幕信息
    screen_config(); 
    ::abs_ScreenX = (displayInfo.height > displayInfo.width ? displayInfo.height : displayInfo.width);
    ::abs_ScreenY = (displayInfo.height < displayInfo.width ? displayInfo.height : displayInfo.width);
    
    ::native_window_screen_x = (displayInfo.height > displayInfo.width ? displayInfo.height : displayInfo.width);
    ::native_window_screen_y = (displayInfo.height > displayInfo.width ? displayInfo.height : displayInfo.width);
    // 初始化imgui
    if (!initGUI_draw(native_window_screen_x, native_window_screen_y, true)) {
        return -1;
    }

        
    printf("当前程序Pid : %d\n", getpid());
    
    #if defined(USE_OPENGL)
        op_img = createTexture_ALL_FromMem(picture_ZhenAiKun_PNG_H, sizeof(picture_ZhenAiKun_PNG_H));
    #else
        LoadTextureFromMemory((const void *)&picture_ZhenAiKun_PNG_H, sizeof(picture_ZhenAiKun_PNG_H), &vk_img);
    #endif
    
    Touch_Init(displayInfo.width, displayInfo.height, displayInfo.orientation, true);
    
    while (main_thread_flag) {    
        // imgui画图开始前调用
        drawBegin(); //
        
        Layout_tick_UI();
        
        drawEnd();// imgui画图结束调用
        std::this_thread::sleep_for(1ms);
    }   
    
    shutdown();
    Touch_Close();
    return 0;
} 


   
void Layout_tick_UI() {
    static bool show_draw_Line = false;
    static bool show_demo_window = false;
    static bool show_another_window = false;
    { 
        static float f = 0.0f;
        static int counter = 0;
        static int style_idx = 1;
        static ImVec4 clear_color = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
        #if defined(USE_OPENGL)
         
        #else
            const static char *name = "(纯c模板4.0)";
        #endif
        ImGui::Begin(name, 0);  // Create a window called "Hello, world!" and append into it.
        ImGui::Text("纯c模板4.0.");               // Display some text (you can use a format strings too)
		if (ImGui::Combo("##主题", &style_idx, "白色主题\0蓝色主题\0紫色主题\0")) {
			switch (style_idx) {
				case 0: ImGui::StyleColorsLight(); break;
				case 1: ImGui::StyleColorsDark(); break;
				case 2: ImGui::StyleColorsClassic(); break;
			}
		}
        
        ImGui::Checkbox("无限血量",&fxk1);//复选框1
            ImGui::SameLine();//在同行
            ImGui::Checkbox("跳高", &fxk2);//复选框2
            ImGui::SameLine();           
            ImGui::Checkbox("关闭跳高", &fxk3);//复选框3
            ImGui::SameLine();
            
            //功能判定拒绝重复执行

            if (fxk1 == 1)
            {
                panding1++;
                if (panding1 == 1) {

                    printf("成功执行功能1");

                   system("chmod 777 gn/无限血量");//给文件777权限
	system("gn/无限血量");//读取编译文件
                    // 
                }

               
            }


            if (fxk2 == 1)
            {
                panding2++;
                if(panding2==1) {
                    printf("成功执行功能2");
                    system("chmod 777 gn/跳高");//给文件777权限
	system("gn/跳高");//读取编译文件

                    // fxk2 = 0;

                }
               
            }
            if (fxk3 == 1)
            {
                panding3++;
                if (panding3==1)
                {
                    printf("成功执行功能3");
                    system("chmod 777 gn/关闭跳高");//给文件777权限
	system("gn/关闭跳高");//读取编译文件

                    // fxk3 = 0;
                }
                }
        
        
        
       
        
        if (ImGui::Button("退出")) {
            main_thread_flag = false;
        }
        g_window = ImGui::GetCurrentWindow();
        ImGui::End();
    }
    
        
    
            
    if (show_demo_window) {
        ImGui::ShowDemoWindow(&show_demo_window);
    }

    if (show_draw_Line)
        ImGui::GetForegroundDrawList()->AddLine(ImVec2(0,0),ImVec2(displayInfo.width, displayInfo.height),IM_COL32(255,0,0,255),4);

}
    



