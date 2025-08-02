
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
	// determine whether the media is copper or serrdes
	switch (hw->phy.media_type) {
	case e1000_media_type_copper:
		/*
		 * link not need check. link is stable
		 */
		if (!hw->mac.get_link_status)
			link_active = !link_active;
			goto out;
		fallthrough;
	case e1000_media_type_internal_serdes:
	default:
	case e1000_media_type_unknown:
		break;
	}

	/*
	 * the setting of this flag acts as a signal to the driver:
	 * the current link status may have changed.
	 *
	 * the driver needs to re-check and confirm the actual link 
	 * status. 
	 *
	 * the flag itself does not directly indicate whether the link
	 * is up or down.
	 */


	/*
	 * to determine whether the MAC type is 210 or 211
	 * for i210/211 chips combined with specific PHY configuration
	 * only
	 */
	if ((hw->mac.type == e1000_i210) || 
	    (hw->mac.type == e1000_i211) && 
	    (hw->phy.id == I210_PHY_ID)) {
		/*
		 * check whether the network device has no carrier
		 * the physical link is not connected
		 *
		 * clear the NEED_LINK_UPDATE flag (indicating that a link update
		 * is not required)
		 * since the no-carrier state is now a confirmed physical condition
		 * and no additional detection is needed
		 */
		if (!netif_carrier_ok(adapter->netdev)) 
			adapter->flags &= ~IGB_FLAG_NEED_LINK_UPDATE;
		/*
		 * if the network device has a carrier (the physical link is connected
		 * properly)
		 * and the NEED_LINK_UPDATE flag is not currently set.
		 * then:
		 * 	set the IGB_FLAG_NEED_LINK_UPDATE bit
		 * 	assign the current kernel timestamp (jiffies) to link check timeout
		 */
		else if (!(adapter->flags & IGB_FLAG_NEED_LINK_UPDATE)) {
			adapter->flags |= IGB_FLAG_NEED_LINK_UPDATE;
			adapter->link_check_timeout = jiffies;
		}	
	}

out:
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
	/*
	 * test and configure the DMA engine inside the i210 NIC to ensure 
	 * it can correctly access the 64-bit physical address space
	 */
	err = dma_set_mask(pci_dev_to_dev(pdev), DMA_BIT_MASK(64));
	if (!err) {
		pci_using_dac = 1;	
	} else {
		err = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
		if (err) {
			dev_err(&pdev->dev,
				"No usable DMA configuration,aborting\n");
			goto err_dma;
		}
	}
}	
