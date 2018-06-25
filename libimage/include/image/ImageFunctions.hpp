// ImageFunctions.hpp

/***************************************************************************
 *   Copyright (C) 2006-2012,2014 Daniel Mueller (deso@posteo.net)         *
 *                                                                         *
 *   This program is free software: you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation, either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>. *
 ***************************************************************************/

#ifndef IMGIMAGEFUNCTIONS_HPP
#define IMGIMAGEFUNCTIONS_HPP

#include <util/Assert.hpp>

#include "image/Config.hpp"
#include "image/ImageAction.hpp"


namespace img
{
  template<typename ReturnT, typename FunctionT>
  ReturnT useImage(ImageBase const& image, FunctionT const& function);

  template<typename ReturnT, typename FunctionT>
  ReturnT useImage(ImageBase& image, FunctionT const& function);
}

namespace img
{
  template<typename ReturnT>
  struct FunctionExecutorBase
  {
    virtual ~FunctionExecutorBase()
    {
    }

    virtual ReturnT execute() const = 0;
  };

  template<typename ReturnT, typename ImageT, typename FunctionT>
  class FunctionExecutor: public FunctionExecutorBase<ReturnT>
  {
  public:
    FunctionExecutor(ImageT& image, FunctionT const& function)
      : image_(&image),
        function_(function)
    {
    }

    virtual ReturnT execute() const override
    {
      return function_(*image_);
    }

  private:
    ImageT* image_;
    FunctionT function_;
  };

  template<typename ReturnT, typename FunctionT>
  class ImageDispatcher: public ImageAction
  {
  public:
    ImageDispatcher(FunctionT const& function)
      : function_(function),
        executor_(nullptr)
    {
    }

    virtual ~ImageDispatcher()
    {
      delete executor_;
    }

    virtual void use(Image<PixelUByteRGBA>& image) override
    {
      createExecutor(image);
    }

    virtual void use(Image<PixelUByteRGB>& image) override
    {
      createExecutor(image);
    }

    virtual void use(Image<PixelUByteA>& image) override
    {
      createExecutor(image);
    }

    virtual void use(Image<PixelUWordRGBA>& image) override
    {
      createExecutor(image);
    }

    virtual void use(Image<PixelUWordRGB>& image) override
    {
      createExecutor(image);
    }

    virtual void use(Image<PixelBitmap>& image) override
    {
      createExecutor(image);
    }

    ReturnT execute()
    {
      return executor_->execute();
    }

  private:
    FunctionT function_;
    FunctionExecutorBase<ReturnT>* executor_;

    template<typename PixelT>
    void createExecutor(Image<PixelT>& image)
    {
      ASSERTOP(executor_, eq, nullptr);
      executor_ = new FunctionExecutor<ReturnT, Image<PixelT>, FunctionT>(image, function_);
    }
  };

  template<typename ReturnT, typename FunctionT>
  class ConstImageDispatcher: public ConstImageAction
  {
  public:
    ConstImageDispatcher(FunctionT const& function)
      : function_(function),
        executor_(nullptr)
    {
    }

    virtual ~ConstImageDispatcher()
    {
      delete executor_;
    }

    virtual void use(Image<PixelUByteRGBA> const& image) override
    {
      createExecutor(image);
    }

    virtual void use(Image<PixelUByteRGB> const& image) override
    {
      createExecutor(image);
    }

    virtual void use(Image<PixelUByteA> const& image) override
    {
      createExecutor(image);
    }

    virtual void use(Image<PixelUWordRGBA> const& image) override
    {
      createExecutor(image);
    }

    virtual void use(Image<PixelUWordRGB> const& image) override
    {
      createExecutor(image);
    }

    virtual void use(Image<PixelBitmap> const& image) override
    {
      createExecutor(image);
    }

    ReturnT execute()
    {
      return executor_->execute();
    }

  private:
    FunctionT function_;
    FunctionExecutorBase<ReturnT>* executor_;

    template<typename PixelT>
    void createExecutor(Image<PixelT> const& image)
    {
      ASSERTOP(executor_, eq, nullptr);
      executor_ = new FunctionExecutor<ReturnT, Image<PixelT> const, FunctionT>(image, function_);
    }
  };


  template<typename ReturnT, typename FunctionT>
  ReturnT useImage(ImageBase const& image, FunctionT const& function)
  {
    ConstImageDispatcher<ReturnT, FunctionT> dispatcher(function);
    image.use(dispatcher);

    return dispatcher.execute();
  }

  template<typename ReturnT, typename FunctionT>
  ReturnT useImage(ImageBase& image, FunctionT const& function)
  {
    ImageDispatcher<ReturnT, FunctionT> dispatcher(function);
    image.use(dispatcher);

    return dispatcher.execute();
  }
}


#endif
