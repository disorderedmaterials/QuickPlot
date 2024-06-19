from cgitb import html

extensions = ["breathe"]

html_theme = "sphinx_rtd_theme"

breathe_projects = {
    "quickplot": "doc_out/xml"
}

# Breathe configuration
breathe_default_project = "quickplot"
