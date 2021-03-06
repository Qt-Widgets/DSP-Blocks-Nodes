#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <QVector>

template< typename T > class Array
{
	Q_DISABLE_COPY( Array< T > )
public:
	inline Array() :
		d( NULL ),
		c( 0 ), s( 0 )
	{}
	inline ~Array()
	{
		::free( d );
	}

	inline bool notEmpty() const
	{
		return s;
	}
	inline int count() const
	{
		return s;
	}

	inline void clear()
	{
		s = 0;
	}
	inline void free()
	{
		::free( d );
		d = NULL;
		c = s = 0;
	}

	inline void alloc( int size, bool setSize = false )
	{
		::free( d );
		d = ( T * )calloc( ( c = size ), sizeof( T ) );
		s = setSize ? size : 0;
	}

	inline void operator =( const QVector< T > &v )
	{
		if ( c < v.count() )
			d = ( T * )realloc( d, ( c = v.count() ) * sizeof( T ) );
		s = v.count();
		memcpy( d, v.data(), s * sizeof( T ) );
	}

	inline void operator +=( const T &t )
	{
		if ( s == c )
			d = ( T * )realloc( d, ++c * sizeof( T ) );
		d[ s++ ] = t;
	}
	inline void operator +=( const Array< T > &other )
	{
		if ( c < s + other.count() )
			d = ( T * )realloc( d, ( c = s + other.count() ) * sizeof( T ) );
		memcpy( d + s, other.data(), other.count() * sizeof( T ) );
		s += other.count();
	}

	inline const T *data() const
	{
		return d;
	}
	inline T *data()
	{
		return d;
	}

	inline const T &operator []( int idx ) const
	{
		return d[ idx ];
	}
	inline T &operator []( int idx )
	{
		return d[ idx ];
	}
private:
	T *d;
	int c, s;
};

#endif // ARRAY_HPP
