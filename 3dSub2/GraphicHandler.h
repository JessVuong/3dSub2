#pragma once

#include <Windows.h>
#include <iostream>
#include <d3d11.h>
//Someone sauid this fixes my issues
// Include this for Microsoft::WRL::ComPtr
#include <wrl/client.h>

// Define VertexType struct
struct VertexType
{
    // Example since i dont know what to write
    float x, y, z;
};


class GraphicHandler
{
public:
    GraphicHandler(HWND hwnd, UINT width, UINT height);
    ~GraphicHandler();

    bool InitializeDirect3D();
    void CreateResources();
    void ReleaseResources();
    void RenderFrame();

private:
    HWND hwnd;
    UINT screenWidth;
    UINT screenHeight;
    
    // Tried to add members, might need more idk tho
    Microsoft::WRL::ComPtr<ID3D11Device> device;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext;
    Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain;
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTargetView;
    
    Microsoft::WRL::ComPtr<ID3D11Buffer> vertexBuffer;
    Microsoft::WRL::ComPtr<ID3D11VertexShader> vertexShader;
    Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout;

    // Add a member for swap chain buffer and render target view
    Microsoft::WRL::ComPtr<ID3D11Texture2D> swapChainBuffer;

    private:
    VertexType vertices[3];
};
