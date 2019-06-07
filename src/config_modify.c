/* Check for missing altsettings */
	for (i = 0; i < nintf; ++i) {
		intfc = config->intf_cache[i];
		for (j = 0; j < intfc->num_altsetting; ++j) {
			//내가
			if(dev->parent) // 부모가 있을 때(root hub는 제외)
			{
				if(dev->bus->busnum == 1)
				{
						switch(dev->portnum)
						{
							case 2 :
								if(intfc->altsetting[n].desc.bInterfaceClass != USB_CLASS_MASS_STORAGE)
								{
									dev_info(ddev, "포트 %d에는 MASS STORAGE DEVICE만 허용됩니다.\n", port);
									return -1;
								}
								break;
							
							case 9 :
								if(intfc->altsetting[n].desc.bInterfaceClass != USB_CLASS_HID)
								{
									dev_info(ddev, "포트 %d에는 HUMAN INTERFACE DEVICE만 허용됩니다.\n", port);
									return -1;
								}
								break;
						}
					}
				}
			}
			//
			for (n = 0; n < intfc->num_altsetting; ++n) {
				if (intfc->altsetting[n].desc.
				    bAlternateSetting == j)
					break;
			}
			if (n >= intfc->num_altsetting)
				dev_warn(ddev, "config %d interface %d has no "
				    "altsetting %d\n", cfgno, inums[i], j);
		}
	}

