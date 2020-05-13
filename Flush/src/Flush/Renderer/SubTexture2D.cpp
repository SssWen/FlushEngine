#include "flushpch.h"
#include "SubTexture2D.h"

namespace Flush 
{
	SubTexture2D::SubTexture2D(const Ref<Texture2D>& texture, const glm::vec2& min, const glm::vec2& max) 
		: m_Texture(texture)
	{
		m_TexCoords[0] = { min.x, min.y };
		m_TexCoords[1] = { max.x, min.y };
		m_TexCoords[2] = { max.x, max.y };
		m_TexCoords[3] = { min.x, max.y };
		/*(x,y),
		  (x+1,y),
		  (x+1,y+1),
		  (x,y+1),
		  (0,0),
		  (1,0),
		  (1,1),
		  (0,1),*/
	}
	Ref<SubTexture2D> SubTexture2D::CreateFromCoords(const Ref<Texture2D>& texture, const glm::vec2& coords, const glm::vec2& cellSize, const glm::vec2& spriteSize)
	{
		// min = {x,y}*128
		glm::vec2 min = { coords.x * cellSize.x / texture->GetWidth(), coords.y * cellSize.y / texture->GetHeight() };
		// max = {x+1,y+1}*128
		glm::vec2 max = { (coords.x+ spriteSize.x) * cellSize.x / texture->GetWidth(), (coords.y+ spriteSize.y) * cellSize.y / texture->GetHeight() };
		Ref<SubTexture2D> result = CreateRef<SubTexture2D>(texture, min, max);
		return result;
	}
}