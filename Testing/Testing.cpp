// Testing.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define SIZEMAP 32
#define MUL_WINDOW 24

SDL_Renderer* gRenderer;
SDL_Window* gMySDLWindow;

bool InitSDL();

using namespace Awesomium;

class TutorialApp : public Application::Listener {
	Application* app_;
	View* view_;
public:
	TutorialApp()
		: app_(Application::Create()),
		view_(0) {
		app_->set_listener(this);
	}

	virtual ~TutorialApp() {
		if (view_)
			app_->DestroyView(view_);
		if (app_)
			delete app_;
	}

	void Run() {
		app_->Run();
	}

	// Inherited from Application::Listener
	virtual void OnLoaded() {
		view_ = View::Create(500, 300);
		// < Set up your View here. >
		// Awesomium::WebURL url(Awesomium::WSLit(m_pAdress));
		//
		//		m_pListener->m_pWebView->LoadURL(url);
		//		do
		//		{
		//			m_pWebCore->Update();
		//		} while (m_pListener->m_pWebView->IsLoading());
		Awesomium::WebURL url(Awesomium::WSLit("file:///test.html"));
		view_->web_view()->LoadURL(url);
	}

	// Inherited from Application::Listener
	virtual void OnUpdate() {
	}

	// Inherited from Application::Listener
	virtual void OnShutdown() {
	}
};


int main(int argc, char *args[])
{
	/*double dZigg;

	double counter = 0;

	for (int i = 0; i < 255; i++)
	{
		dZigg = ZigguratNRandom();

		cout << dZigg << endl;

		counter += dZigg;
	}*/
	

	/*InitSDL();

	SDL_RenderClear(gRenderer);

	FractalNoise Test(0/ *UIRand()* /);
	Test.SetOctaves(15);
	Test.SetBaseFrequency(0.7);
	Test.SetScale(0.2);
	Test.SetPersistence(0.1);
	Test.SetLacunarity(6.0);

	double value;

	std::vector<double> tempvec;

	for (int i = 0; i < SIZEMAP; ++i)
	{
		for (int j = 0; j < SIZEMAP; ++j)
		{
			value = Test.Noise(i, j, 0.5);

			tempvec.push_back(value);

			Uint8 color = (uint8)(value * 255);
			SDL_SetRenderDrawColor(gRenderer, color, color, color, 255);
			for (int x = 0; x < MUL_WINDOW; ++x)
			{
				for (int y = 0; y < MUL_WINDOW; ++y)
				{
					SDL_RenderDrawPoint(gRenderer, i*MUL_WINDOW + x, j*MUL_WINDOW + y);
				}
			}

		}
	}

	/ *for (int i = 0; i < SIZEMAP*MUL_WINDOW; ++i)
	{
		for (int j = 0; j < SIZEMAP*MUL_WINDOW; ++j)
		{
			value = Test.noise(i, j, 0.5);

			Uint8 color = (uint8)(value * 255);
			SDL_SetRenderDrawColor(gRenderer, color, color, color, 255);
			SDL_RenderDrawPoint(gRenderer, i, j);
		}
	}* /

	SDL_RenderPresent(gRenderer);
	
	SDL_DestroyWindow(gMySDLWindow);
	SDL_DestroyRenderer(gRenderer);*/

	TutorialApp app;
	app.Run();

    return 0;
}

bool InitSDL()
{
	string ErrorMessage = "There was a trouble initializing SDL \n";
	bool Succeed = true;
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		cout << ErrorMessage << endl;
		Succeed = false;
	}
	else
	{
		gMySDLWindow = SDL_CreateWindow("My First SDL Project", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SIZEMAP*MUL_WINDOW, SIZEMAP*MUL_WINDOW, SDL_WINDOW_SHOWN);
		if (gMySDLWindow != NULL)
		{
			gRenderer = SDL_CreateRenderer(gMySDLWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer != NULL)
			{
				SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				Succeed = true;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					Succeed = false;
				}
				if (TTF_Init() == -1)
				{
					printf("TTF_init could not initialize! SDL_image Error: %s\n", IMG_GetError());
					Succeed = false;
				}
			}
			else
			{
				Succeed = false;
			}
		}
		else
		{
			cout << ErrorMessage << endl;
			Succeed = false;
		}
	}

	return Succeed;
}

