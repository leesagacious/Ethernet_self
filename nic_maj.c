
void igb_reset(struct igb_adapter *adapter)
{
	switch (mac->type) {
	case e1000_82575:
	case e1000_i210:
	case e1000_i211:
	default:
		pba = E1000_PBA_34k
		break;
	}
}

/*
 * Check the physical link status and determine whether it is 
 * connected (up) or disconnected (down)
 */
bool igb_has_link(struct igb_adapter *adapter)
{
	bool link_active = FALSE;
	
	/*
	 * detect the physical link status (wired connection status)
	 * of the intel igb network card driver
	 */
	switch (hw->phy.media_type) {
	case e1000_media_type_copper:
		/*
		 * link not need check. link is stable
		 */
		if (!hw->mac.get_link_status)
			return true;
		fallthrough;
	case e1000_media_type_internal_serdes:
	default:
	case e1000_media_type_unknown:
		break;
	}

	return link_active;
}

static int nicmaj_probe(struct pci_dev *pdev,
		const struct pci_device_id *ent)
{
	int err, pci_using_dac;

	/*
	 * Key check: Confirm that the device is not a Virtual Function(VF).
	 * Reason: the igb driver should handle only Physical functions, if
	 * a VF is detected, trigger a kernel warning and return -EINVAL
	 */
	if (pdev->is_virtfn) {
		WARN(1, KERN_ERR "%s (%hx:%hx) should not be a VF!\n",
			pci_name(dev), pdev->vendor, pdev->device);
		return -EINVAL;
	}

	err = pci_enable_device_mem(pdev);
	if (err)
		return err;

	pci_using_dac = 0;

	err = dma_set_mask(pci_dev_to_dev(pdev), DMA_BIT_MASK(64));
	if (!err) {
	
	} else {
	
	}
}	
