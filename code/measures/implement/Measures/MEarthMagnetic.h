//# MEarthMagnetic.h: A Measure: Magnetic field on Earth
//# Copyright (C) 1995,1996,1997,1998,1999,2000
//# Associated Universities, Inc. Washington DC, USA.
//#
//# This library is free software; you can redistribute it and/or modify it
//# under the terms of the GNU Library General Public License as published by
//# the Free Software Foundation; either version 2 of the License, or (at your
//# option) any later version.
//#
//# This library is distributed in the hope that it will be useful, but WITHOUT
//# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
//# FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
//# License for more details.
//#
//# You should have received a copy of the GNU Library General Public License
//# along with this library; if not, write to the Free Software Foundation,
//# Inc., 675 Massachusetts Ave, Cambridge, MA 02139, USA.
//#
//# Correspondence concerning AIPS++ should be addressed as follows:
//#        Internet email: aips2-request@nrao.edu.
//#        Postal address: AIPS++ Project Office
//#                        National Radio Astronomy Observatory
//#                        520 Edgemont Road
//#                        Charlottesville, VA 22903-2475 USA
//#
//#
//# $Id$

#if !defined(AIPS_MEARTHMAGNETIC_H)
#define AIPS_MEARTHMAGNETIC_H

//# Includes
#include <aips/aips.h>
#include <aips/Measures/MeasBase.h>
#include <aips/Measures/MeasRef.h>
#include <aips/Quanta/MVEarthMagnetic.h>

//# Forward Declarations
class MEarthMagnetic;
class MCEarthMagnetic;
template <class M> class MeasConvert;
template <class M> class ArrayMeasColumn;
template <class M> class ROArrayMeasColumn;
template <class M> class ScalarMeasColumn;
template <class M> class ROScalarMeasColumn;

//# Typedefs

// <summary> A Measure: Magnetic field on Earth </summary>

// <use visibility=export>

// <reviewed reviewer="" date="yyyy/mm/dd" tests="" demos="">
// </reviewed>

// <prerequisite>
//   <li> <linkto class=Measure>Measure</linkto> class 
// </prerequisite>
//
// <etymology>
// Earth and Magnetic field
// </etymology>
//
// <synopsis>
// MEarthMagnetic forms derived Measure class for Earth' magnetic flux density.
// The field can be specified as a model, or as a 3D vector (see
// <linkto class=MVEarthMagnetic>MVEarthMagnetic</linkto>) with a specified
// reference frame code. If a model is specified, a possibly specified
// explicit field will be ignored, since the field will be calculated from
// the model if a conversion is asked for.<br>
// The class contains the following magnetic field models:
// <ul>
//   <li> IGRF		international reference field
// </ul>
// The reference frame type can be any of the types specified in the
// <linkto class=MDirection>MDirection</linkto> direction types (e.g. AZEL).
// <note role=warning>
// The IGRF needs a Table of coefficients (at 5-year interval) </note>
//
// Conversion between field models is not supported (but not relevant
// anyway with only one model supported). Conversion to an explicit direction
// is done by the standard <linkto class=MeasConvert>MeasConvert</linkto>
// class and rules (see example) using <em>MEarthMagnetic::Convert</em>, 
// and the reference types (e.g. MEarthMagnetic::AZEL).
//
// An <linkto class=EarthMagneticMachine> EarthMagneticMachine</linkto> has
// been provided to get e.g. the field in a certain direction at a
// certain height.
//
// </synopsis>
//
// <example>
// <srcblock>
// // Where on Earth
// MPosition pos(MVPosition(Quantity(20,'m'), Quantity(5,'deg'), 
//                          Quantity(52,'deg')), MPosition::WGS84);
// // Time we want it
// MEpoch epo(MVEpoch(50000));
// // Put in frame
// MeasFrame frame(pos, epo);
// // Magnetic field model
// MEarthMagnetic mf;
// // Show field strength in Gauss in AzEl system
// cout <<
//   MEarthMagnetic::Convert(mf, MEarthMagnetic::AZEL)().
//		getValue().getLength("G") << endl;
// </srcblock>
// </example>
//
// <motivation>
// To have the Earth' magnetic field in the standard Measure environment.
// </motivation>
//
// <todo asof="2000/06/15">
//	<li> maybe add other field models if necessary (e.g. dipole)
// </todo>

class MEarthMagnetic : public MeasBase<MVEarthMagnetic, MeasRef<MEarthMagnetic> >  {

 public:
  //# Friends
  // Conversion of data
  friend class MeasConvert<MEarthMagnetic>;

  //# Enumerations
  // Types of known MEarthMagnetics
  // <note role=tip> The order defines the order in the translation matrix
  // FromTo
  // in the getConvert routine in MCEarthMagnetic. Do not change the order
  // without changing the array. Additions should be made before N_types, and
  // an additional row and column should be coded in FromTo, and
  // in showType().</note>
  enum Types {
    ITRF,
    J2000,
    JMEAN,
    JTRUE,
    APP,
    B1950,
    BMEAN,
    BTRUE,
    GALACTIC,
    HADEC,
    AZEL,
    AZELSW,
    JNAT,
    ECLIPTIC,  
    MECLIPTIC,
    TECLIPTIC,
    SUPERGAL,
    N_Types,
    // Models. First one should be IGRF
    IGRF = 32,
    N_Models,
    // All extra bits (for internal use only)
    EXTRA = 32,
    // Defaults
    DEFAULT=IGRF,
    // Synonyms
    AZELNE=AZEL 
  };

  //# Typedefs
  // Measure value container for this class (i.e. MEarthMagnetic::MVType)
  typedef class MVEarthMagnetic MVType;
  // Measure conversion routines for this class (i.e. MEarthMagnetic::MCType)
  typedef class MCEarthMagnetic MCType;
  // Measure reference (i.e. MEarthMagnetic::Ref)
  typedef class MeasRef<MEarthMagnetic> Ref;
  // Measure Convert (i.e. MEarthMagnetic::Convert)
  typedef class MeasConvert<MEarthMagnetic> Convert;
  // Measure table Columns (e.g., MEarthMagnetic::ROScalarColumn)
  typedef class ROScalarMeasColumn<MEarthMagnetic> ROScalarColumn;
  typedef class ScalarMeasColumn<MEarthMagnetic> ScalarColumn;
  typedef class ROArrayMeasColumn<MEarthMagnetic> ROArrayColumn;
  typedef class ArrayMeasColumn<MEarthMagnetic> ArrayColumn;
  // Reference enum Types (included originally for gcc 2.95)  
  typedef Types Types;

//# Constructors
// <note> In the following constructors and other functions, all 
// <em>MeasRef</em> can be replaced with simple <src>Measure::TYPE</src>
// where no offsets or frames are needed in the reference. </note>
// Default constructor; generates the default IGRF type
    MEarthMagnetic();
// Create from data and reference
// <group>
    MEarthMagnetic(const MVEarthMagnetic &dt);
    MEarthMagnetic(const MVEarthMagnetic &dt, const MEarthMagnetic::Ref &rf);
    MEarthMagnetic(const MVEarthMagnetic &dt, MEarthMagnetic::Types rf);
    MEarthMagnetic(const Measure *dt);
    MEarthMagnetic(const MeasValue *dt);
    MEarthMagnetic(const MEarthMagnetic::Ref &rf);
// </group>

  // <group>
  MEarthMagnetic(const MEarthMagnetic &);
  MEarthMagnetic &operator=(const MEarthMagnetic &);
  // </group>

//# Destructor
    virtual ~MEarthMagnetic();

//# Operators

//# General Member Functions
// Tell me your type
// <group>
    virtual const String &tellMe() const;
    static const String &showMe();
    virtual uInt type() const;
    static void assure(const Measure &in);
// </group>
// Translate reference code. The uInt version has a check for valid codes
  // (i.e. it is a safe cast).
  // <thrown>
  //   <li> AipsError in the uInt interface if illegal code given
  // </thrown>
  // <group>
  static MEarthMagnetic::Types castType(uInt tp);
  static const String &showType(MEarthMagnetic::Types tp);
  static const String &showType(uInt tp);
  // </group>
// Translate string to reference code
// <group>
  static Bool getType(MEarthMagnetic::Types &tp, const String &in);
  Bool giveMe(MEarthMagnetic::Ref &mr, const String &in);
// </group>
  // Set the offset in the reference (False if non-matching Measure)
  virtual Bool setOffset(const Measure &in);
  // Set the reference type to the specified String. False if illegal
  // string, reference set to DEFAULT.
  virtual Bool setRefString(const String &in);
  // Get the default reference type
  virtual const String &getDefaultType() const;
  // Get a list of all known reference codes. nall returns the number in list,
  // nextra the number of specials (like planets) that should be at 
  // end of list). typ returns the list of corresponding types.
  // <group>
  virtual const String *const allTypes(Int &nall, Int &nextra,
				       const uInt *&typ) const;
  static const String *const allMyTypes(Int &nall, Int &nextra,
					const uInt *&typ);
  // </group>
  // Get the reference type (for records, including codes like R_)
  virtual String getRefString() const;
  // Get my type (as Register)
  static uInt myType();
  // Tell me if you are a pure model (e.g. a planet)
  virtual Bool isModel() const;

// Get Measure data
// <group>
    Quantum<Vector<Double> > get(const Unit &inunit) const;
    Quantum<Vector<Double> > getAngle() const;
    Quantum<Vector<Double> > getAngle(const Unit &inunit) const;
// </group>

// Make copy
  virtual Measure *clone() const;

private:
//# Enumerations

//# Data

//# Member functions

};

#endif
