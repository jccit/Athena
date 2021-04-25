/** @type {import('@docusaurus/types').DocusaurusConfig} */
module.exports = {
  title: 'Athena Engine',
  tagline: 'Dinosaurs are cool',
  url: 'https://athena-docs.netlify.app/',
  baseUrl: '/',
  onBrokenLinks: 'throw',
  onBrokenMarkdownLinks: 'warn',
  favicon: 'img/favicon.ico',
  organizationName: 'jccit', // Usually your GitHub org/user name.
  projectName: 'athena', // Usually your repo name.
  themeConfig: {
    sidebarCollapsible: false,
    navbar: {
      title: 'Athena',
      logo: {
        alt: 'My Site Logo',
        src: 'img/logo.svg',
      },
      items: [
        {
          type: 'doc',
          docId: 'guides/welcome',
          position: 'left',
          label: 'Guides',
        },
        {
          type: 'doc',
          docId: 'api/index',
          position: 'left',
          label: 'API',
        },
        {
          href: 'https://github.com/jccit/Athena',
          label: 'GitHub',
          position: 'right',
        },
      ],
    },
    footer: {
      style: 'dark',
      links: [
        {
          title: 'Links',
          items: [
            {
              label: 'GitHub',
              to: 'https://github.com/jccit/Athena',
            },
          ],
        },
      ],
      copyright: `Copyright © ${new Date().getFullYear()} Athena Engine. Built with Docusaurus.`,
    },
  },
  presets: [
    [
      '@docusaurus/preset-classic',
      {
        docs: {
          sidebarPath: require.resolve('./sidebars.js'),
          // Please change this to your repo.
          editUrl:
            'https://github.com/facebook/docusaurus/edit/master/website/',
        },
        theme: {
          customCss: require.resolve('./src/css/custom.css'),
        },
      },
    ],
  ],
};
