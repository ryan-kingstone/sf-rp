/* Copyright (C) Ryan Kingstone - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential.
 * Written by Ryan Kingstone <ryan.kingstone@outlook.com>
 */

stock strcpyEx(dest[], const source[], maxlength=sizeof dest)
{
	strcat((dest[0] = EOS, dest), source, maxlength);
}