#pragma once

namespace fast_io::details
{

template<std::integral char_type,std::size_t base,bool upper,bool transparent>
inline constexpr auto cal_content()
{
	constexpr std::size_t chars{2};
	constexpr std::size_t pw{base*base};
	std::array<std::array<char_type,chars>,pw> vals{};
	for(std::size_t i(1);i<pw;++i)
	{
		auto& val(vals[i]);
		val=vals[i-1];
		std::size_t j(chars);
		for(;j--;)
		{
			if(val[j]==base-1)
				val[j]=0;
			else
				break;
		}
		++val[j];
	}
	if constexpr(!transparent)
	{
	if constexpr(exec_charset_is_ebcdic<char_type>())
	{
/*
http://www.astrodigital.org/digital/ebcdic.html#:~:text=The%20EBCDIC%20Character%20Table%20Once%20upon%20a%20time,that%20is%20used%20in%20the%20IBM%20mainframe%20environment.
*/
		for(auto &e : vals)
			for(auto &e1 : e)
				if(e1<10)
					e1+=0xF0;
				else if(e1<19)
				{
					if constexpr(upper)
						e1+=0xC1-10;
					else
						e1+=0x81-10;
				}
				else if(e1<28)
				{
					if constexpr(upper)
						e1+=0xD1-19;
					else
						e1+=0x91-19;
				}
				else
				{
					if constexpr(upper)
						e1+=0xE2-28;
					else
						e1+=0xA2-28;
				}
	}
	else
	{
		for(auto &e : vals)
			for(auto &e1 : e)
				if(e1<10)
					e1+=0x30;
				else
				{
					if constexpr(upper)
						e1+=0x41-10;
					else
						e1+=0x61-10;
				}
	}
	}
	return vals;
}

template<std::integral char_type,std::size_t base,bool upper,bool transparent=false>
struct shared_static_base_table
{
	inline static constexpr auto table=cal_content<char_type,base,upper,transparent>();
};
}
