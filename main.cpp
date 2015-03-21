#include<iostream>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>

using namespace std;

const int SCREEN_HEIGHT = 480;
const int SCREEN_WIDTH = 640;

bool init( SDL_Window* &window,  SDL_Renderer* &renderer );	//start SDL and create window
void close( SDL_Window* &window, SDL_Renderer* &renderer);	//frees media and shuts down SDL
void hexIncr(int & val);
void drawCircle(SDL_Renderer* renderer, int x, int y, int radius);
void drawFilledCircle(SDL_Renderer * renderer, int x, int y, int radius);

int main( int argc, char* argv[] ){

	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Texture* texture = NULL;
	if( init(window, renderer) ){
		bool quit = false;
		SDL_Event e;
		int redVal = 0x00;
		int greenVal = 0x00;
		int blueVal = 0x00;
		
		//set background color
		SDL_SetRenderDrawColor( renderer, 0x9f, 0xb6, 0xcd, 0xFF );
		SDL_RenderClear( renderer );
		//draw original circle
		SDL_SetRenderDrawColor( renderer, redVal, greenVal, blueVal, 0xFF);
		
		int vertBuffer = (SCREEN_WIDTH / 8) - (SCREEN_HEIGHT / 8);
		drawFilledCircle(renderer, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 8 + vertBuffer, SCREEN_HEIGHT / 8);
		drawFilledCircle(renderer, SCREEN_WIDTH / 2, 7 * SCREEN_HEIGHT / 8 - vertBuffer, SCREEN_HEIGHT / 8);
		drawFilledCircle(renderer, SCREEN_WIDTH / 8, SCREEN_HEIGHT / 2, SCREEN_HEIGHT / 8);
		drawFilledCircle(renderer, 7 * SCREEN_WIDTH / 8, SCREEN_HEIGHT / 2, SCREEN_HEIGHT / 8);
		
		
		
		//draws lines to ensure symmetry
//		SDL_RenderDrawLine(renderer, (SCREEN_WIDTH / 2) - (SCREEN_HEIGHT / 8), 0,
//												(SCREEN_WIDTH / 2) - (SCREEN_HEIGHT / 8), SCREEN_HEIGHT);
//		SDL_RenderDrawLine(renderer, (SCREEN_WIDTH / 2) + (SCREEN_HEIGHT / 8), 0,
//												(SCREEN_WIDTH / 2) + (SCREEN_HEIGHT / 8), SCREEN_HEIGHT);
//		SDL_RenderDrawLine(renderer, 0, (SCREEN_HEIGHT / 2) - (SCREEN_HEIGHT / 8), 
//												SCREEN_WIDTH, (SCREEN_HEIGHT / 2) - (SCREEN_HEIGHT / 8) );
//		SDL_RenderDrawLine(renderer, 0, (SCREEN_HEIGHT / 2) + (SCREEN_HEIGHT / 8), 
//												SCREEN_WIDTH, (SCREEN_HEIGHT / 2) + (SCREEN_HEIGHT / 8) );
		
		
		
		SDL_RenderPresent(renderer);
		
		while( !quit ){
			while( SDL_PollEvent( &e ) != 0 ){
			
				if(e.type == SDL_QUIT){
					quit = true;
				} 
				else if (e.type == SDL_KEYDOWN){
					
					switch(e.key.keysym.sym){
						case SDLK_UP:
							hexIncr(redVal);
							SDL_SetRenderDrawColor( renderer, redVal, 0x00, 0x00, 0xFF);
							drawFilledCircle(renderer, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 8 + vertBuffer, 														SCREEN_HEIGHT / 8);
							break;
						case SDLK_RIGHT:
							hexIncr(greenVal);
							SDL_SetRenderDrawColor( renderer, 0x00, greenVal, 0x00, 0xFF);
							drawFilledCircle(renderer, 7 * SCREEN_WIDTH / 8, SCREEN_HEIGHT / 2, 
													SCREEN_HEIGHT / 8);
							break;
						case SDLK_LEFT:
							hexIncr(blueVal);
							SDL_SetRenderDrawColor( renderer, 0x00, 0x00, blueVal, 0xFF);
							drawFilledCircle(renderer, SCREEN_WIDTH / 8, SCREEN_HEIGHT / 2, SCREEN_HEIGHT / 8);
							break;
						case SDLK_DOWN:
							redVal = 0x00;
							greenVal = 0x00;
							blueVal = 0x00;
							break;
						default:
							break;
					}
				
					SDL_SetRenderDrawColor( renderer, redVal, greenVal, blueVal, 0xFF);
					drawFilledCircle( renderer, SCREEN_WIDTH / 2, SCREEN_HEIGHT/2, SCREEN_HEIGHT / 8);
					SDL_RenderPresent( renderer );
					
				}
	
			}
		}	
	}
	
	close( window, renderer);
	return 0;
}

bool init(SDL_Window* &window, SDL_Renderer* &renderer ){
	bool success = true;
	
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
		cout<<"Initialization failed. " << SDL_GetError() << endl;
		success = false;
	
	} else {
		
		window = SDL_CreateWindow( "Color Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
											SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
											
		if( window == NULL ){
			cout<<"Window could not be created. " << SDL_GetError() << endl;
			success = false;
		
		} else {
			renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED);
			if(renderer == NULL){
				cout<<"Renderer could not be created. " << SDL_GetError() <<endl;
				success = false;
			} else { 
				SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
			}
		}
	}
	
	return success;
}

void close( SDL_Window* &window, SDL_Renderer* &renderer){
	
	SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow( window );
	renderer = NULL;
	window = NULL;
	SDL_Quit();
}

void hexIncr(int & val){
	int incrementValue = 0x04;
	if( val < (0xFF - incrementValue) ){
		val += incrementValue;
	} else {
		val = 0xFF;
	}
	cout<<val<<endl;
}

void drawCircle(SDL_Renderer * renderer, int x, int y, int radius){
	int xi = radius;
	int yi = 0;
	int error = xi -  1;
	
	while(xi >= yi){
		cout<<"asd"<<endl;
		SDL_RenderDrawPoint(renderer, xi + x, yi + y);
		SDL_RenderDrawPoint(renderer, yi + x, xi + y);
		SDL_RenderDrawPoint(renderer, xi + x, 0 - yi + y);
		SDL_RenderDrawPoint(renderer, yi + x, 0 - xi + y);
		SDL_RenderDrawPoint(renderer, 0 - xi + x, yi + y);
		SDL_RenderDrawPoint(renderer, 0 - yi + x, xi + y);
		SDL_RenderDrawPoint(renderer, 0 - xi + x, 0 - yi + y);
		SDL_RenderDrawPoint(renderer, 0 - yi + x, 0 - xi + y);
		yi++;
		
		if(error < 0){
			error += 2 * yi + 1;
		} else {
			xi--;
			error += 2 * (yi -xi) + 1;
		}
		
	}
}

void drawFilledCircle(SDL_Renderer * renderer, int x, int y, int radius){
	int xi = radius;
	int yi = 0;
	int error = xi -  1;
	
	while(xi >= yi){
		cout<<"asd"<<endl;
		SDL_RenderDrawLine(renderer, xi + x, yi + y, 0 - xi + x, 0 - yi + y );
		SDL_RenderDrawLine(renderer, yi + x, xi + y, 0 - yi + x, 0 - xi + y );
		SDL_RenderDrawLine(renderer, xi + x, 0 - yi + y, 0 - xi + x, yi + y );
		SDL_RenderDrawLine(renderer, yi + x, 0 - xi + y, 0 - yi + x, xi + y );
		//SDL_RenderDrawPoint(renderer, 0 - xi + x, yi + y);
		//SDL_RenderDrawPoint(renderer, 0 - yi + x, xi + y);
		//SDL_RenderDrawPoint(renderer, 0 - xi + x, 0 - yi + y);
		//SDL_RenderDrawPoint(renderer, 0 - yi + x, 0 - xi + y);
		yi++;
		
		if(error < 0){
			error += 2 * yi + 1;
		} else {
			xi--;
			error += 2 * (yi -xi) + 1;
		}
		
	}
}





























