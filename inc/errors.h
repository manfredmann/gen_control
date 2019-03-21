/*
 * Generator control tool
 *
 * Copyright 2019 by Roman Serov <roman@serov.co>
 *
 * This file is part of Generator control tool.
 *
 * Generator control tool is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Generator control tool is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Generator control tool. If not, see <http://www.gnu.org/licenses/>.
 *
 * @license GPL-3.0+ <http://spdx.org/licenses/GPL-3.0+>
*/

#ifndef ERRORS_H
#define ERRORS_H

#include <string>
#include <iostream>
#include <libusb-1.0/libusb.h>

namespace USBErrors {
  class USBTransferException {
    public:
      USBTransferException(int error) {
        //this->msg = std::string(libusb_error_name(error));
        errCode = error;
        switch(error) {
          case LIBUSB_ERROR_IO: {
            this->msg = "USB Input/output error";
            break;
          }
          case LIBUSB_ERROR_INVALID_PARAM: {
            this->msg = "USB Invalid parameter";
            break;
          }
          case LIBUSB_ERROR_ACCESS: {
            this->msg = "USB Access denied (insufficient permissions)";
            break;
          }
          case LIBUSB_ERROR_NOT_FOUND: {
            this->msg = "USB Entity not found";
            break;
          }
          case LIBUSB_ERROR_BUSY: {
            this->msg = "USB Resource busy";
            break;
          }
          case LIBUSB_ERROR_INTERRUPTED: {
            this->msg = "USB System call interrupted (perhaps due to signal)";
            break;
          }
          case LIBUSB_ERROR_NO_MEM: {
            this->msg = "USB Insufficient memory";
            break;
          }
          case LIBUSB_ERROR_NOT_SUPPORTED: {
            this->msg = "USB Operation not supported or unimplemented on this platform";
            break;
          }
          case LIBUSB_ERROR_TIMEOUT: {
            this->msg = "USB transfer timed out";
            break;
          }
          case LIBUSB_ERROR_PIPE: {
            this->msg = "USB endpoint halted";
            break;
          }
          case LIBUSB_ERROR_OVERFLOW: {
            this->msg = "USB device offered more data";
            break;
          }
          case LIBUSB_ERROR_NO_DEVICE: {
            this->msg = "USB device has been disconnected";
            break;
          }
          default: {
            this->msg = "USB Unresolved error";
          }
        }
      }
      std::string getError() {
        return this->msg;
      }
      int getErrorCode() {
        return this->errCode;
      }
    private:
      std::string msg;
      int errCode;
  };

  class USBException {
    public:
      USBException(int error) {
        this->errCode = error;
        switch(error) {
          case -1: {
            this->msg = "Couldn't find device";
            break;
          }
          case -2: {
            this->msg = "Couldn't detach kernel driver";
            break;
          }
          case -3: {
            this->msg = "Claim interface error";
            break;
          }
          default: {
            this->msg = "USB Unresolved error";
          }
        }
      }
      std::string getError() {
        return this->msg;
      }
      int getErrorCode() {
        return this->errCode;
      }

    private:
      std::string msg;
      int errCode;
    };
};

#endif // ERRORS_H
