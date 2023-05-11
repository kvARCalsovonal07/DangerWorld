#ifndef __IMAGEMANAGER_HPP__
#define __IMAGEMANAGER_HPP__

#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>

class Image_manager
{
private:
	std::map<std::string, sf::Image> image_map;

public:
	const sf::Image& GetImage(std::string image_path) // The filename is used as a key
	{
		// Is this image is not loaded - load it
		if(image_map.find(image_path) == image_map.end())
		{
			sf::Image tmp;
			if(!tmp.loadFromFile(image_path))
			{
				exit(EXIT_FAILURE);
			}

			image_map.insert( std::pair<std::string,sf::Image>(image_path,tmp) );
		}

		return image_map[image_path];
	}

	void InformUs() const
	{
		std::cout << "These are the images we have loaded:" << std::endl;
		for(std::map<std::string, sf::Image>::const_iterator it = image_map.begin(); it != image_map.end(); ++it)
		{
		   std::cout << it->first << std::endl;
		}
	}
};


#endif // __IMAGEMANAGER_HPP_