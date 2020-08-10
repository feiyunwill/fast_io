#pragma once

namespace fast_io
{

template<typename T>
struct basic_io_scatter_t
{
	T const* base;
	std::size_t len;
	inline explicit operator basic_io_scatter_t<void>() const noexcept requires(!std::same_as<T,void>)
	{
		return {base,len*sizeof(T)};
	}
};

//should be binary compatible with POSIX's iovec

using io_scatter_t = basic_io_scatter_t<void>;

template<typename T>
struct basic_message_hdr
{
	T const        *msg_name;       /* Optional address */
	std::size_t     msg_namelen;    /* Size of address */
	basic_io_scatter_t<T> *msg_iov;        /* Scatter/gather array */
	std::size_t   msg_iovlen;     /* # elements in msg_iov */
	T const       *msg_control;    /* Ancillary data, see below */
	std::size_t   msg_controllen; /* Ancillary data buffer len */
	int           msg_flags;      /* Flags (unused) */
	inline explicit operator basic_message_hdr<void>() const noexcept requires(!std::same_as<T,void>)
	{
		return {msg_name,msg_namelen*sizeof(T),msg_iov,msg_iovlen*sizeof(T),msg_control,msg_controllen,msg_flags};
	}
};

using message_hdr = basic_message_hdr<void>;
//should be binary compatible with POSIX's msghdr

template<typename T>
class io_message_t
{
public:
	using type = typename std::remove_cvref_t<decltype(io_message_type(*static_cast<T*>(nullptr)))>::type;
};

template<typename T>
class io_async_scheduler_t
{
public:
	using type = typename std::remove_cvref_t<decltype(async_scheduler_type(*static_cast<T*>(nullptr)))>::type;
};

template<typename T>
class io_async_overlapped_t
{
public:
	using type = typename std::remove_cvref_t<decltype(async_overlapped_type(*static_cast<T*>(nullptr)))>::type;
};

template<typename T,bool end_test=false>
struct io_reserve_type_t
{
	explicit constexpr io_reserve_type_t() = default;
};
template<typename T,bool end_test=false>
inline constexpr io_reserve_type_t<T,end_test> io_reserve_type{};

template<typename T>
struct print_scatter_type_t
{
	explicit constexpr print_scatter_type_t() = default;
};

template<typename T>
inline constexpr print_scatter_type_t<T> print_scatter_type{};

}