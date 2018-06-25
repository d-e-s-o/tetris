#!/usr/bin/perl -w

#/***************************************************************************
# *   Copyright (C) 2012 Daniel Mueller (deso@posteo.net)                   *
# *                                                                         *
# *   This program is free software: you can redistribute it and/or modify  *
# *   it under the terms of the GNU General Public License as published by  *
# *   the Free Software Foundation, either version 3 of the License, or     *
# *   (at your option) any later version.                                   *
# *                                                                         *
# *   This program is distributed in the hope that it will be useful,       *
# *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
# *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
# *   GNU General Public License for more details.                          *
# *                                                                         *
# *   You should have received a copy of the GNU General Public License     *
# *   along with this program.  If not, see <http://www.gnu.org/licenses/>. *
# ***************************************************************************/


use warnings;
use strict;

use File::Basename;


my $argc = scalar(@ARGV);

if ($argc != 2)
{
  print "invalid number of arguments\n";
  print "usage: $ARGV[0] <input file> <output file>\n";
  exit -1;
}

my $input = "$ARGV[0]";
my $output = "$ARGV[1]";

if (! -f "$input")
{
  print "invalid input file given\n";
  exit -2;
}

open(FILE, $input) or die($!);

my $attributes;
my $smethods;
my $vmethods;
my $vattributes;
my $vinit;
my $imethods;
my $count = 0;

while( my $line = <FILE>) {
  chomp($line);
  $count++;
  my ($type, $attribute, $default, $valid, $description) = split('\s*\|\s*', $line);

  my $adefault;
  $adefault = $default;
  $adefault =~ s/"/\\"/g;

  $attributes .= sprintf <<EOF;
    {\"$attribute\", \"$adefault\", \"$description\"},
EOF

  $smethods .= sprintf <<EOF;
  public:
    $type get$attribute() const
    {
      $type value = get${attribute}Impl();

      if (is${attribute}Valid(value))
        return value;

      return get${attribute}Default();
    }

    void set$attribute($type const& value)
    {
      if (is${attribute}Valid(value))
        set${attribute}Impl(value);
    }

  protected:
    virtual $type get${attribute}Impl() const = 0;
    virtual void set${attribute}Impl($type const& value) = 0;\

    bool is${attribute}Valid($type value) const
    {
      return $valid;
    }

    $type get${attribute}Default() const
    {
      return $default;
    }

EOF

  $vmethods .= sprintf <<EOF;
    virtual $type get${attribute}Impl() const
    {
      return $attribute;
    }

    virtual void set${attribute}Impl($type const& value)
    {
      $attribute = value;
    }

EOF

  $vattributes .= sprintf <<EOF;
    $type $attribute;
EOF

  $vinit .= sprintf <<EOF;
      $attribute(get${attribute}Default()),
EOF

  $imethods .= sprintf <<EOF;
    virtual $type get${attribute}Impl() const
    {
      $type value = get${attribute}Default();
      ini_.readValue("Settings", "$attribute", value);

      return value;
    }

    virtual void set${attribute}Impl($type const& value)
    {
      ini_.writeValue("Settings", "$attribute", value);
    }

EOF
}

close(FILE);

# remove trailing newline and trailing comma
chomp($vinit);
chop($vinit);

my $guard;
$guard =  uc(basename($output));
$guard =~ tr/.-/_/;

my $header = sprintf <<EOF, basename($output);
// %s

#ifndef TTRS$guard
#define TTRS$guard

#include <base/IniFile.hpp>
#include "tetris/String.hpp"


namespace ttrs
{
  struct Attribute
  {
    char const* const name_;
    char const* const default_;
    char const* const description_;
  };


  Attribute const attributes[] =
  {
$attributes
  };

  size_t const attribute_count = $count;


  class Settings
  {
  public:
    virtual ~Settings()
    {
    }

$smethods
  };

  class VolatileSettings: public Settings
  {
  public:
    VolatileSettings() :
$vinit
    {
    }

$vmethods
  private:
$vattributes
  };

  class IniSettings: public Settings
  {
  public:
    IniSettings(ctr::StringA const& file)
      : ini_(file.toString()),
        file_(file)
    {
    }

    virtual ~IniSettings()
    {
      ini_.saveToFile(file_.toString());
    }

$imethods
  private:
    base::IniFile ini_;
    ctr::StringA file_;
  };
}


#endif
EOF

open(FILE, ">$output") or die($!);
print(FILE $header);
close(FILE);
