// #include "ImGui/ImGuiLayer.h"
// #include "Application/Application.h"
// #include "Logs/Log.h"
// #include "pch.h"

// #include "imgui.h"
// #include "imgui_impl_glfw.h"
// #include "imgui_impl_opengl3.h"
// #include <stdio.h>

// // #include <GLFW/glfw3.h>

// namespace Hanabi {

//     ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer") {}

//     void ImGuiLayer::OnAttach() {

//         HANABI_CORE_INFO("ImGui Layer On Attach");

//         const char *glsl_version = "#version 410";
//         glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//         glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
//         glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 3.2+ only
//         glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);           // Required on Mac

//         // Application &app = Application::Get();
//         // GLFWwindow *window = static_cast<GLFWwindow *>(app.GetWindow().GetNativeWindow());

//         GLFWwindow *window = glfwCreateWindow(600, 360, "ImGui", NULL, NULL);
//         glfwMakeContextCurrent(window);

//         IMGUI_CHECKVERSION();
//         ImGui::CreateContext();

//         ImGuiIO &io = ImGui::GetIO();
//         (void)io;
//         ImGui::StyleColorsDark();
//         ImGui_ImplGlfw_InitForOpenGL(window, true);
//         ImGui_ImplOpenGL3_Init(glsl_version);

//         bool show_demo_window = true;
//         ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

//         while (!glfwWindowShouldClose(window)) {

//             glfwPollEvents();
//             ImGui_ImplOpenGL3_NewFrame();
//             ImGui_ImplGlfw_NewFrame();
//             ImGui::NewFrame();
//             ImGui::ShowDemoWindow(&show_demo_window);
//             static float f = 0.0f;
//             static int counter = 0;

//             ImGui::Begin("Hello, world!"); // Create a window called "Hello, world!" and append into it.

//             ImGui::Text("This is some useful text.");          // Display some text (you can use a format strings too)
//             ImGui::Checkbox("Demo Window", &show_demo_window); // Edit bools storing our window open/close state

//             ImGui::SliderFloat("float", &f, 0.0f, 1.0f);             // Edit 1 float using a slider from 0.0f to 1.0f
//             ImGui::ColorEdit3("clear color", (float *)&clear_color); // Edit 3 floats representing a color

//             if (ImGui::Button("Button")) // Buttons return true when clicked (most widgets return true when edited/activated)
//                 counter++;
//             ImGui::SameLine();
//             ImGui::Text("counter = %d", counter);

//             ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
//             ImGui::End();

//             ImGui::Render();
//             int display_w, display_h;
//             glfwGetFramebufferSize(window, &display_w, &display_h);
//             glViewport(0, 0, display_w, display_h);
//             glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
//             glClear(GL_COLOR_BUFFER_BIT);
//             ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

//             glfwSwapBuffers(window);
//         }
//     }

//     void ImGuiLayer::OnDetach() {
//         ImGui_ImplOpenGL3_Shutdown();
//         ImGui_ImplGlfw_Shutdown();
//         ImGui::DestroyContext();
//     }

//     void ImGuiLayer::OnEvent(Event &e) {
//     }

//     void ImGuiLayer::Begin() {}
//     void ImGuiLayer::End() {}

//     void ImGuiLayer::SetDarkThemeColors() {}

//     void ImGuiLayer::OnUpdate() {
//     }
// }